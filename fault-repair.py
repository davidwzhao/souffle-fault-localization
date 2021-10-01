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

        print('chosen:', m)

        # remove m from set_cover_problem
        set_cover_problem.pop(m[0])

        # invalidate trees covered by m
        for t in m[1]:
            covered[t] = True

            for tup in trees[t]:
                print('trees[t]:', trees[t])
                set_cover_problem[tup].discard(t)

        tuples.append(m[0])

    return tuples

def main():
    souffle_instance = faultbase.initIncSouffle(problem_dir, "query", "facts")

    
    # give incremental update
    with open(os.path.join(problem_dir, 'update.in'), 'r') as update_file:
        for l in update_file:
            l = l.rstrip()
            faultbase.execSouffleCmd(souffle_instance, l)

    all_prov = faultbase.getAllProv(souffle_instance, 'path(0, 3)')

    c = construct_minimum_set_cover(all_prov)

    print(c)

    print(solve_minimum_set_cover(all_prov, c))



    # set up reverse souffle instance
    # faultbase.applyDiffToInput(problem_dir, 'update.in', 'facts', 'facts_reverse')
    # faultbase.reverseDiff(problem_dir, 'update.in', 'update_reverse.in')

    # reverse_souffle_instance = faultbase.initIncSouffle(problem_dir, "query", 'facts_reverse')


if __name__ == '__main__':
    main()
