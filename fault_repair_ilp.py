#!/usr/bin/python3

# Fault repair algorithm

import faultbase

import collections
import os
import sys
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

    # maintain a set of edb_tuples, we need these for the ILP optimization target
    edb_tuples = set()

    def walk_prov_tree(p):
        nonlocal repair_ilp
        nonlocal ilp_vars
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
                    head_tup_var = pulp.LpVariable(head_tup, lowBound=0, upBound=1, cat='Integer')
                    ilp_vars[head_tup] = head_tup_var

                for body_tup in current_body_tuples:
                    if body_tup not in ilp_vars:
                        body_tup_var = pulp.LpVariable(body_tup, lowBound=0, upBound=1, cat='Integer')
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
    ilp.solve(pulp.apis.GLPK_CMD())
    # ilp.solve()

    repair = set()
    for tup in edb_tuples:
        # print(tup, ilp_vars[tup].varValue)
        if ilp_vars[tup].varValue == 0:
            repair.add(tup)

    return repair

def repair_faults(souffle_instance, faults):
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

    return repair

    # repair = set()

    # trees = []
    # for f in faults:
    #     trees.extend(faultbase.getAllProv(souffle_instance, f))

    # c = construct_minimum_set_cover(trees)
    # return solve_minimum_set_cover(trees, c)
