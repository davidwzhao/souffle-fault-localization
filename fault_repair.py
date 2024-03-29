#!/usr/bin/python3

# Fault repair algorithm

import faultbase

import collections
import os
import sys
import pulp as pl

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

    set_cover_ilp = pl.LpProblem("Set Cover", pl.LpMinimize)
    tuples = pl.LpVariable.dicts("tuples", set_cover_problem.keys(), cat='Integer')

    for tup in set_cover_problem.keys():
        tuples[tup].bounds(0, 1)

    # objective function
    set_cover_ilp += sum([tuples[tup] for tup in set_cover_problem.keys()])

    # constraints that every tree must be covered
    for (idx, _) in enumerate(trees):
        set_cover_ilp += pl.lpSum([tuples[tup] for tup in set_cover_problem.keys() if idx in set_cover_problem[tup]]) >= 1

    # solve
    set_cover_ilp.solve(pl.apis.PULP_CBC_CMD(logPath=""))

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
    repair = set()

    trees = []
    for f in faults:
        trees.extend(faultbase.getAllProv(souffle_instance, f))

    c = construct_minimum_set_cover(trees)
    return solve_minimum_set_cover(trees, c)

def get_all_trees(souffle_instance, faults):
    trees = dict()
    for f in faults:
        trees[f] = faultbase.getAllProv(souffle_instance, f)

    return trees

def replace_negations_with_trees(trees, negation_trees):

    result = collections.defaultdict(list)

    def replace_negations(key_tup, tree):
        res = []

        changed = False
        for (idx, leaf) in enumerate(tree):
            if leaf[0] == '!':
                tup = faultbase.remove_diff_suffix(leaf[1:])

                if tup in negation_trees:
                    changed = True
                    for n in negation_trees[tup]:
                        res.append(tree[:idx] + n + tree[idx+1:])
                break

        if changed:
            for t in res:
                # do it again, since there might be more negations
                replace_negations(key_tup, t)
        else:
            result[key_tup].append(tree)

    for tup in trees:
        for t in trees[tup]:
            replace_negations(tup, t)

    return dict(result)

def flip_insert_remove_trees(trees):
    for key_tup in trees:
        for tree in trees[key_tup]:
            for i in range(len(tree)):
                tree[i] = faultbase.flip_insert_remove(tree[i])

    return trees

def repair_all_faults(souffle_instance, reverse_souffle_instance, faults, reverse_faults):
    trees = {}

    # reset faults, as they are all processed so far
    negations = set()
    while len(faults) > 0 or len(reverse_faults) > 0:

        # process positive faults
        fault_trees = get_all_trees(souffle_instance, faults)
        trees = replace_negations_with_trees(trees, {k: fault_trees[k] for k in negations})
        trees.update({k: fault_trees[k] for k in fault_trees.keys() if k not in negations})

        negations = set()
        faults = []

        # check for negations for negated tuples and add to reverse_faults
        for ts in trees.values():
            for tree in ts:
                for t in tree:
                    if t[0] == '!':
                        tup = faultbase.remove_diff_suffix(t[1:])
                        reverse_faults.append(tup)
                        negations.add(tup)

        reverse_fault_trees = get_all_trees(reverse_souffle_instance, reverse_faults)
        reverse_fault_trees = flip_insert_remove_trees(reverse_fault_trees)
        trees = replace_negations_with_trees(trees, {k: reverse_fault_trees[k] for k in negations})
        trees.update({k: reverse_fault_trees[k] for k in reverse_fault_trees.keys() if k not in negations})

        negations = set()
        reverse_faults = []

        # check for negations for positive tuples and add to faults
        for ts in trees.values():
            for tree in ts:
                for t in tree:
                    if t[0] == '!':
                        tup = faultbase.remove_diff_suffix(t[1:])
                        faults.append(tup)
                        negations.add(tup)

    flattened_trees = [t for key in trees for t in trees[key]]

    msc = construct_minimum_set_cover(flattened_trees)
    repair = solve_minimum_set_cover(flattened_trees, msc)

    return repair

def main():
    # Get input problem directory name
    problem_dir = sys.argv[1]

    souffle_instance = faultbase.initIncSouffle(problem_dir, "query", "facts")

    # set up reverse souffle instance
    faultbase.applyDiffToInput(problem_dir, 'update.in', 'facts', 'facts_reverse')
    faultbase.reverseDiff(problem_dir, 'update.in', 'update_reverse.in')

    reverse_souffle_instance = faultbase.initIncSouffle(problem_dir, "query", 'facts_reverse')

    # get faults
    faults = []
    reverse_faults = []

    with open(os.path.join(problem_dir, 'faults.txt'), 'r') as faults_file:
        for l in faults_file:
            l = l.rstrip()

            (kind, tup) = tuple(l.split(' ', maxsplit=1))

            if kind == 'existing':
                faults.append(tup)

            if kind == 'missing':
                reverse_faults.append(tup)

    # initialize souffle instance updates
    faultbase.apply_update(souffle_instance, os.path.join(problem_dir, 'update.in'))
    faultbase.execSouffleCmd(souffle_instance, 'storediffs')

    faultbase.apply_update(reverse_souffle_instance, os.path.join(problem_dir, 'update_reverse.in'))
    faultbase.execSouffleCmd(reverse_souffle_instance, 'storediffs')

    return repair_all_faults(souffle_instance, reverse_souffle_instance, faults, reverse_faults)

if __name__ == '__main__':
    print(main())
