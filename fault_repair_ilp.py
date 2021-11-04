#!/usr/bin/python3

# Fault repair algorithm

import faultbase

import collections
import os
import sys
import time
import pulp

# The problem directory should contain:
# 1. query - the incremental souffle executable
# 2. facts/<relation>.facts - the inputs for each relation
# 3. update.in - the diff
# 4. faults.txt - the faults

# Algorithm:
# - compute all-provenance of each fault
# - construct a minimum set cover problem
# - run some approximation algorithm for the minimum set cover

def construct_repair_ilp(trees):
    # initialize ILP problem instance
    repair_ilp = pulp.LpProblem("Repair", pulp.LpMaximize)

    # maintain a dict of vars so we don't create a new LP var each time
    ilp_vars = {}
    current_ilp_var_num = 0

    # maintain a set of edb_tuples, we need these for the ILP optimization target
    edb_tuples = set()

    def walk_prov_tree(p):
        nonlocal repair_ilp
        nonlocal ilp_vars
        nonlocal current_ilp_var_num
        nonlocal edb_tuples

        if 'axiom' in p:
            if faultbase.isDiff(p['axiom']):
                edb_tuples.add(p['axiom'])
            return

        # go through alternative children
        cNum = 0

        while 'children_' + str(cNum) in p:
            c = 'children_' + str(cNum)

            # get body tuples for current child
            current_body_tuples = []
            for child in p[c]:
                if 'axiom' in child:
                    if faultbase.isDiff(child['axiom']):
                        current_body_tuples.append(child['axiom'])
                elif 'premises' in child:
                    if faultbase.isDiff(child['premises']):
                        current_body_tuples.append(child['premises'])

            # create a constraint using the body tuples
            if 'premises' in p:
                # create constraint
                head_tup = p['premises']

                # create variables for head and body tuples
                if head_tup not in ilp_vars:
                    head_tup_var = pulp.LpVariable('var_' + str(current_ilp_var_num), lowBound=0, upBound=1, cat='Integer')
                    current_ilp_var_num += 1
                    ilp_vars[head_tup] = head_tup_var

                for body_tup in current_body_tuples:
                    if body_tup not in ilp_vars:
                        body_tup_var = pulp.LpVariable('var_' + str(current_ilp_var_num), lowBound=0, upBound=1, cat='Integer')
                        current_ilp_var_num += 1
                        ilp_vars[body_tup] = body_tup_var

                # create constraint!
                constraint_body = [head_tup]
                constraint_body += current_body_tuples
                constraint = pulp.lpSum([ilp_vars[x] * (-1 if x == head_tup else 1) for x in constraint_body]) <= len(current_body_tuples) - 1
                # print("constraint:", constraint, "premises:", head_tup, "body_tups:", current_body_tuples)
                repair_ilp += constraint
            else:
                # something is wrong
                print("something is wrong, we have a proof tree with no premises for the head???")

            # recurse on child
            for child in p[c]:
                walk_prov_tree(child)

            cNum += 1

    for tree in trees:
        walk_prov_tree(tree)
        fault_constraint = (ilp_vars[tree['premises']] == 0)

        # print("fault constraint:", fault_constraint)
        repair_ilp += fault_constraint

    # create maximization target
    target = pulp.lpSum([ilp_vars[e] for e in edb_tuples])
    # print("target:", target)
    repair_ilp += target

    return (edb_tuples, ilp_vars, repair_ilp)

def solve_repair_ilp(edb_tuples, ilp_vars, ilp):
    ilp.solve(pulp.apis.GLPK_CMD(msg=0))
    # ilp.solve()

    repair = set()
    for tup in edb_tuples:
        # print(tup, ilp_vars[tup].varValue)
        if ilp_vars[tup].varValue == 0:
            repair.add(tup)

    return repair

def repair_current_level_faults(souffle_instance, faults):
    # The idea here is to create an ILP based on the proof trees for the faults.
    # For each one-step proof t_1, ..., t_k => t, we create the ILP constraint
    # t_1 + ... + t_k - t <= k - 1
    # 
    # Each t_i is a 0-1 integer
    # The fault tuple t_bad = 0
    # The optimization constraint is to maximize sum of {EDB tuples t}


    # get json and walk it
    trees = []
    for f in faults:
        tree = faultbase.getAllProvJson(souffle_instance, f)

        if 'axiom' in tree and tree['axiom'] == 'Tuple not found':
            continue

        trees.append(tree)

    if trees == []:
        return ([], [])

    (edb_tuples, ilp_vars, repair_ilp) = construct_repair_ilp(trees)

    # repair_ilp.solve(pulp.apis.PULP_CBC_CMD(logPath=""))
    repair = solve_repair_ilp(edb_tuples, ilp_vars, repair_ilp)

    return (trees, repair)

    # repair = set()

    # trees = []
    # for f in faults:
    #     trees.extend(faultbase.getAllProv(souffle_instance, f))

    # c = construct_minimum_set_cover(trees)
    # return solve_minimum_set_cover(trees, c)

def tuple_exists(souffle_instance, tup):
    # set depth to 1, then try to compute provenance, then check whether tuple
    # is found

    faultbase.execSouffleCmd(souffle_instance, 'setdepth 1')
    tree = faultbase.getAllProvJson(souffle_instance, tup)

    tuple_exists = True
    if 'axiom' in tree and tree['axiom'] == 'Tuple not found':
        tuple_exists = False

    faultbase.execSouffleCmd(souffle_instance, 'setdepth 10000')

    return tuple_exists

def get_reverse_tuple_diff(t):
    if t.startswith("!"):
        t = t[1:]

    if t.endswith("(-)"):
        return "insert " + faultbase.remove_diff_suffix(t)
    elif t.endswith("(+)"):
        return "remove " + faultbase.remove_diff_suffix(t)

def repair_faults(souffle_instance, faults):
    # Here, we repair faults level by level. In the first level, we compute a
    # repair based on all the proof trees of that height. Then, we reverse the
    # tuples that appear in the repair, and go again
    #
    # Now, each level produces a set of proof trees. We take this total set of
    # proof trees and compute and solve a Repair ILP. However, this result may
    # actually exclude some proof trees, because they were not fully disabled by
    # the earlier levels. Therefore, we must repeat the process until we
    # actually find a full repair.

    startTime = time.time()

    total_reversed_tuples = []
    total_trees = []
    while True:
        total_current_repair = set()
        while True:
            (current_trees, current_repair) = repair_current_level_faults(souffle_instance, faults)

            # print("current repair:", current_repair)

            if len(current_repair) == 0:
                # we have no more proof trees!
                break

            total_current_repair.update(current_repair)

            total_trees.extend(current_trees)

            # disable each tuple that occurs in current_repair
            for t in current_repair:
                reverse_tup_string = get_reverse_tuple_diff(t)

                faultbase.execSouffleCmd(souffle_instance, reverse_tup_string)
                total_reversed_tuples.append(reverse_tup_string)

            faultbase.execSouffleCmd(souffle_instance, 'commit')

        if len(total_trees) == 0:
            return set()

        # Now, take trees and compute and solve an ILP
        (edb_tuples, ilp_vars, repair_ilp) = construct_repair_ilp(total_trees)
        repair = solve_repair_ilp(edb_tuples, ilp_vars, repair_ilp)

        if set(repair) == set(total_current_repair):
            # this is equal to the total set of repair computed before, so is
            # so is guaranteed to be a correct repair
            for r in total_reversed_tuples:
                faultbase.execSouffleCmd(souffle_instance, faultbase.reverseDiffLine(r))

            faultbase.execSouffleCmd(souffle_instance, 'commit')

            endTime = time.time()
            faultbase.logTime('repair_faults', endTime - startTime)

            return repair

        # Use current repair
        current_repair_strings = set()
        for r in repair:
            reverse_tup_string = get_reverse_tuple_diff(r)
            current_repair_strings.add(reverse_tup_string)

        current_reversed_strings = set()
        for r in total_reversed_tuples:
            current_reversed_strings.add(r)

        for r in current_repair_strings - current_reversed_strings:
            faultbase.execSouffleCmd(souffle_instance, r)

        for r in current_reversed_strings - current_repair_strings:
            faultbase.execSouffleCmd(souffle_instance, faultbase.reverseDiffLine(r))

        total_reversed_tuples = list(current_repair_strings)

        faultbase.execSouffleCmd(souffle_instance, 'commit')

        # Check if the fault is actually solved
        faults_fixed = True
        for f in faults:
            if tuple_exists(souffle_instance, f):
                # print("tuple", f, "not repaired")
                faults_fixed = False

        if faults_fixed:
            # restore previous state
            for r in total_reversed_tuples:
                faultbase.execSouffleCmd(souffle_instance, faultbase.reverseDiffLine(r))

            faultbase.execSouffleCmd(souffle_instance, 'commit')

            endTime = time.time()
            faultbase.logTime('repair_faults', endTime - startTime)

            return repair
