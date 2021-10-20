#!/usr/bin/python3

# Fault localization algorithm

import sys
import os
import faultbase

# The problem directory should contain:
# 1. query - the incremental souffle executable
# 2. facts/<relation>.facts - the inputs for each relation
# 3. update.in - the diff
# 4. faults.txt - the faults

# Algorithm:
# - iniitialize incremental souffle
# - give incremental update
# - read fault tuples and compute provenance

# localize a set of faults from faults_file
def localize_faults(souffle_instance, faults):
    localization = set()

    for f in faults:
        localization.update(faultbase.getOneProv(souffle_instance, f))

    return localization

def localize_all_faults(problem_dir, souffle_instance, reverse_souffle_instance, faults, reverse_faults):

    # now do the localization algo!
    localizations = set()

    while len(faults) > 0 or len(reverse_faults) > 0:
        localizations.update(localize_faults(souffle_instance, faults))

        # now faults are processed, so reset faults
        faults = []

        # check for any negations
        for l in localizations:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                reverse_faults.append(tup)

        localizations -= set([l for l in localizations if l[0] == '!'])

        ls_reverse = localize_faults(reverse_souffle_instance, reverse_faults)
        ls_reverse = set(map(faultbase.flip_insert_remove, ls_reverse))
        localizations.update(ls_reverse)

        reverse_faults = []

        # check for any negations
        for l in localizations:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                faults.append(tup)

        localizations -= set([l for l in localizations if l[0] == '!'])

    return localizations

def main():
    # Get input problem directory name
    problem_dir = sys.argv[1]

    souffle_instance = faultbase.initIncSouffle(problem_dir, "query")

    # set up reverse souffle instance
    faultbase.applyDiffToInput(problem_dir, 'update.in', 'facts', 'facts_reverse')
    faultbase.reverseDiff(problem_dir, 'update.in', 'update_reverse.in')

    reverse_souffle_instance = faultbase.initIncSouffle(problem_dir, "query", 'facts_reverse')

    # initialize souffle instance updates
    faultbase.apply_update(souffle_instance, os.path.join(problem_dir, 'update.in'))
    faultbase.execSouffleCmd(souffle_instance, 'storediffs')

    faultbase.apply_update(reverse_souffle_instance, os.path.join(problem_dir, 'update_reverse.in'))
    faultbase.execSouffleCmd(reverse_souffle_instance, 'storediffs')

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

    return localize_all_faults(problem_dir, souffle_instance, reverse_souffle_instance, faults, reverse_faults)

if __name__ == '__main__':
    print(main())
