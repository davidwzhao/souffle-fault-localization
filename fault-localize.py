#!/usr/bin/python3

# Fault localization algorithm

import sys
import os
import faultbase

# Get input problem directory name
problem_dir = sys.argv[1]

# The problem directory should contain:
# 1. query - the incremental souffle executable
# 2. <relation>.facts - the inputs for each relation
# 3. update.in - the diff
# 4. faults.txt - the faults

# Algorithm:
# - iniitialize incremental souffle
# - give incremental update
# - read fault tuples and compute provenance

if __name__ == '__main__':
    souffle_instance = faultbase.initIncSouffle(problem_dir, "query")

    # give incremental update
    with open(os.path.join(problem_dir, 'update.in'), 'r') as update_file:
        for l in update_file:
            faultbase.execSouffleCmd(souffle_instance, l)

    # check faults
