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

def construct_minimum_set_cover(trees):
    # trees is a list of lists of tuples
    # e.g. [[e(1, 2), e(2, 3)], [e(1, 4), e(4, 3)]]

    # the minimum set cover instance should have the set of tuples as a carrier
    # set, with each subset being the set of proof trees that the tuple appears
    # in

    set_cover_problem = collections.defaultdict(set)

    for (idx, tree) in enumerate(trees):
        for tup in tree:
            set_cover_problem[tup].add(idx)

    return set_cover_problem

def solve_minimum_set_cover(trees, set_cover_problem):
    # a very simple greedy algorithm that gives a ln(n) approximation (or
    # something like that)

    # ILP SOLUTION STARTS HERE
    if len(set_cover_problem) == 0:
        return []

    set_cover_ilp = pulp.LpProblem("Set Cover", pulp.LpMinimize)
    tuples = pulp.LpVariable.dicts("tuples", set_cover_problem.keys(), cat='Integer')

    for tup in set_cover_problem.keys():
        tuples[tup].bounds(0, 1)

    # objective function
    set_cover_ilp += sum([tuples[tup] for tup in set_cover_problem.keys()])

    # constraints that every tree must be covered
    for (idx, _) in enumerate(trees):
        set_cover_ilp += pulp.lpSum([tuples[tup] for tup in set_cover_problem.keys() if idx in set_cover_problem[tup]]) >= 1

    # solve
    set_cover_ilp.solve(pulp.apis.PULP_CBC_CMD(logPath=""))

    # get result
    selected_tuples = []

    for tup in set_cover_problem.keys():
        if tuples[tup].varValue == 1:
            selected_tuples.append(tup)

    return selected_tuples

    # APPROXIMATION SOLUTION STARTS HERE
    # if len(set_cover_problem) == 0:
    #     return []

    # covered = [False for t in trees]
    # tuples = []

    # while not all(covered):
    #     # take max number of covered elements
    #     m = max(set_cover_problem.items(), key=(lambda x: len(x[1])))

    #     # remove m from set_cover_problem
    #     set_cover_problem.pop(m[0])

    #     # invalidate trees covered by m
    #     for t in m[1]:
    #         covered[t] = True

    #         for tup in trees[t]:
    #             # print("discarding", t, "from", tup)
    #             set_cover_problem[tup].discard(t)

    #     # print("covered:", len(covered))

    #     # print("set cover problem:", set_cover_problem)

    #     uncovered = []
    #     for (idx, c) in enumerate(covered):
    #         if c == False:
    #             uncovered.append(idx)

    #     # print(uncovered)

    #     tuples.append(m[0])

    # return tuples

def repair_faults(souffle_instance, faults):
    # The idea here is to create an ILP based on the proof trees for the faults.
    # For each one-step proof t_1, ..., t_k => t, we create the ILP constraint
    # t_1 + ... + t_k - t <= k - 1
    # 
    # Each t_i is a 0-1 integer
    # The fault tuple t_bad = 0
    # The optimization constraint is to maximize sum of {EDB tuples t}

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
                print("constraint:", constraint, "premises:", head_tup, "body_tups:", current_body_tuples)
                repair_ilp += constraint
            else:
                # something is wrong
                print("something is wrong, we have a proof tree with no premises for the head???")

            # recurse on child
            for child in p[c]:
                walk_prov_tree(child)

            cNum += 1

    # get json and walk it
    for f in faults:
        tree = faultbase.getAllProvJson(souffle_instance, f)
        walk_prov_tree(tree)
        fault_constraint = (ilp_vars[tree['premises']] == 0)
        print("fault constraint:", fault_constraint)
        repair_ilp += fault_constraint

    # create maximization target
    target = pulp.lpSum([ilp_vars[e] for e in edb_tuples])
    print("target:", target)
    repair_ilp += target

    repair_ilp.solve(pulp.apis.PULP_CBC_CMD(logPath=""))

    repair = set()
    for tup in edb_tuples:
        print(tup, ilp_vars[tup].varValue)
        if ilp_vars[tup].varValue == 0:
            repair.add(tup)

    return repair

    # repair = set()

    # trees = []
    # for f in faults:
    #     trees.extend(faultbase.getAllProv(souffle_instance, f))

    # c = construct_minimum_set_cover(trees)
    # return solve_minimum_set_cover(trees, c)
