#!/usr/bin/python3

# Fault repair algorithm

import sys
import os
import faultbase

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

def main():
    souffle_instance = faultbase.initIncSouffle(problem_dir, "query", "facts")

    
    # give incremental update
    with open(os.path.join(problem_dir, 'update.in'), 'r') as update_file:
        for l in update_file:
            l = l.rstrip()
            faultbase.execSouffleCmd(souffle_instance, l)

    print(faultbase.getAllProv(souffle_instance, 'path(0, 3)'))


    # set up reverse souffle instance
    # faultbase.applyDiffToInput(problem_dir, 'update.in', 'facts', 'facts_reverse')
    # faultbase.reverseDiff(problem_dir, 'update.in', 'update_reverse.in')

    # reverse_souffle_instance = faultbase.initIncSouffle(problem_dir, "query", 'facts_reverse')


if __name__ == '__main__':
    main()
