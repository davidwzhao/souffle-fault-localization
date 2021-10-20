#!/usr/bin/python3

import os
import sys

import faultbase
import fault_localize
import fault_repair

def localize(souffle_instance, reverse_souffle_instance, faults, reverse_faults):
    # now do the localization algo!
    localizations = set()

    while len(faults) > 0 or len(reverse_faults) > 0:
        localizations.update(fault_localize.localize_faults(souffle_instance, faults))

        # now faults are processed, so reset faults
        faults = []

        # check for any negations
        for l in localizations:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                reverse_faults.append(tup)

        localizations -= set([l for l in localizations if l[0] == '!'])

        # for reverse faults, we have to do a repair
        ls_reverse = fault_repair.repair_faults(reverse_souffle_instance, reverse_faults)
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

def repair(souffle_instance, reverse_souffle_instance, faults, reverse_faults):
    # now do the localization algo!
    repairs = set()

    while len(faults) > 0 or len(reverse_faults) > 0:
        repairs.update(fault_repair.repair_faults(souffle_instance, faults))

        # now faults are processed, so reset faults
        faults = []

        # check for any negations
        for l in repairs:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                reverse_faults.append(tup)

        repairs -= set([l for l in repairs if l[0] == '!'])

        # for reverse faults, we have to do a localize
        ls_reverse = fault_localize.localize_faults(reverse_souffle_instance, reverse_faults)
        ls_reverse = set(map(faultbase.flip_insert_remove, ls_reverse))
        repairs.update(ls_reverse)

        reverse_faults = []

        # check for any negations
        for l in repairs:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                faults.append(tup)

        repairs -= set([l for l in repairs if l[0] == '!'])

    return repairs

def main():
    mode = sys.argv[1]
    problem_dir = sys.argv[2]

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

    print("faults: ", faults, ", reverse_faults: ", reverse_faults)

    
    result = set()
    if mode == 'localize':
        result = localize(souffle_instance, reverse_souffle_instance, faults, reverse_faults)
    elif mode == 'repair':
        result = repair(souffle_instance, reverse_souffle_instance, faults, reverse_faults)
    else:
        print("Mode is 'localize' or 'repair'")

    return result

if __name__ == '__main__':
    print(main())
