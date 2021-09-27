#!/usr/bin/python3

# Fault localization algorithm

import sys
import faultbase

# Get input problem directory name
problem_dir = sys.argv[1]

# The problem directory should contain:
# 1. query - the incremental souffle executable
# 2. <relation>.facts - the inputs for each relation
# 3. update.in - the diff
# 4. faults.txt - the faults


