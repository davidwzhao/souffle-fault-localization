#!/usr/bin/python3

# Fault repair algorithm

import faultbase

import collections
import os
import sys

# Get input problem directory name
problem_dir = sys.argv[1]

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

    covered = [False for t in trees]
    tuples = []

    while not all(covered):
        # take max number of covered elements
        m = max(set_cover_problem.items(), key=(lambda x: len(x[1])))

        # remove m from set_cover_problem
        set_cover_problem.pop(m[0])

        # invalidate trees covered by m
        for t in m[1]:
            covered[t] = True

            for tup in trees[t]:
                set_cover_problem[tup].discard(t)

        tuples.append(m[0])

    return tuples

def repair_faults(souffle_instance, update_file, faults):
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

def apply_update(souffle_instance, update_file):
    with open(os.path.join(problem_dir, update_file), 'r') as update_file:
        for l in update_file:
            l = l.rstrip()
            faultbase.execSouffleCmd(souffle_instance, l)

def remove_diff(s):
    return s.removesuffix(' (-)').removesuffix(' (+)')

def flip_insert_remove(t):
    res = t
    if t.endswith("(-)") or t.endswith("(+)"):
        if t[-2] == '+':
            res = t[:-2] + '-)'
        elif t[-2] == '-':
            res = t[:-2] + '+)'

    return res

def replace_negations_with_trees(trees, negation_trees):

    result = []

    def replace_negations(tree):
        res = []

        changed = False
        for (idx, leaf) in enumerate(tree):
            if leaf[0] == '!':
                tup = remove_diff(leaf[1:])

                if tup in negation_trees:
                    changed = True
                    for n in negation_trees[tup]:
                        res.append(tree[:idx] + list(map(flip_insert_remove, n)) + tree[idx+1:])
                break

        if changed:
            for t in res:
                # do it again, since there might be more negations
                replace_negations(t)
        else:
            result.append(tree)

    for tup in trees:
        for t in trees[tup]:
            replace_negations(t)

    print(result)


def main():
    trees = {'path(0, 3)': [['edge(1, 2) (+)', 'edge(2, 3) (+)'], ['edge(1, 5) (+)', 'edge(5, 3) (+)'], ['edge(0, 4) (+)', 'edge(4, 5) (+)', 'edge(5, 3) (+)']], 'path2(0, 3)': [['edge(1, 2) (+)', 'edge(2, 3) (+)'], ['edge(1, 5) (+)', 'edge(5, 3) (+)'], ['edge(0, 4) (+)', '!edge(4, 5) (+)', '!edge(5, 3) (+)']]}

    negation_trees = {'edge(5, 3)': [['asdf', 'asdfer'], ['hello']], 'edge(4, 5)': [['edgeasdf'], ['what is this']]}

    replace_negations_with_trees(trees, negation_trees)

    exit(0)

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

    # initialize things
    # first do positive faults
    apply_update(souffle_instance, 'update.in')

    # get trees
    trees = get_all_trees(souffle_instance, faults)
    print(trees)

    while len(faults) > 0 or len(reverse_faults) > 0:

        # check for negations and add to reverse_faults
        for (tup, ts) in trees.items():
            for t in ts:
                if t[0] == '!':
                    tup = t[1:].removesuffix(' (-)').removesuffix(' (+)')
                    reverse_faults.append(tup)

        # process reverse faults
        apply_update(reverse_souffle_instance, 'update_reverse.in')

        # get all trees for reverse faults
        reverse_fault_trees = get_all_trees(reverse_souffle_instance, reverse_faults)

        # add reverse




if __name__ == '__main__':
    main()
