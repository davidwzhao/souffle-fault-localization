#!/usr/bin/python3

import logging
import os
import sys
import time

import faultbase
import fault_localize
import fault_repair_ilp

def localize(souffle_instance, reverse_souffle_instance, faults, reverse_faults):
    # now do the localization algo!
    localizations = set()
    num_iterations = 0

    while len(faults) > 0 or len(reverse_faults) > 0:
        num_iterations += 1
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
        ls_reverse = fault_repair_ilp.repair_faults(reverse_souffle_instance, reverse_faults)
        ls_reverse = set(map(faultbase.flip_insert_remove, ls_reverse))
        localizations.update(ls_reverse)

        reverse_faults = []

        # check for any negations
        for l in localizations:
            if l[0] == '!':
                tup = faultbase.remove_diff_suffix(l[1:])
                faults.append(tup)

        localizations -= set([l for l in localizations if l[0] == '!'])

    logging.info("localization took " + str(num_iterations) + " iterations")

    return localizations

def repair(souffle_instance, reverse_souffle_instance, faults, reverse_faults):
    # now do the localization algo!
    repairs = set()
    num_iterations = 0

    while len(faults) > 0 or len(reverse_faults) > 0:
        num_iterations += 1
        repairs.update(fault_repair_ilp.repair_faults(souffle_instance, faults))

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

    logging.info("repair took " + str(num_iterations) + " iterations")

    return repairs

def get_excluded_tuples():
    excluded_tuples = []
    while True:
        try:
            current_tuple = input("input a tuple to exclude > ")
            excluded_tuples.append(current_tuple)
        except EOFError:
            break

    return excluded_tuples

def main():
    mode = sys.argv[1]
    problem_dir = sys.argv[2]
    allow_user_interaction = len(sys.argv) > 3 and sys.argv[3] == '1'

    initSouffleStart = time.time()
    souffle_instance = faultbase.initIncSouffle(problem_dir, "query")
    # print("finished initializing souffle, about to initialize reverse souffle")

    # set up reverse souffle instance
    faultbase.applyDiffToInput(problem_dir, 'update.in', 'facts', 'facts_reverse')
    # print("finished applying diff to input")
    faultbase.reverseDiff(problem_dir, 'update.in', 'update_reverse.in')
    # print("finished reversing original diff")

    reverse_souffle_instance = faultbase.initIncSouffle(problem_dir, "query", 'facts_reverse')
    # print("finished initializing reverse souffle")

    # initialize souffle instance updates
    faultbase.apply_update(souffle_instance, os.path.join(problem_dir, 'update.in'))
    # print("finished executing forwards update")
    faultbase.execSouffleCmd(souffle_instance, 'storediffs')
    # print("  finished storing diffs")

    faultbase.apply_update(reverse_souffle_instance, os.path.join(problem_dir, 'update_reverse.in'))
    # print("finished executing reverse update")
    faultbase.execSouffleCmd(reverse_souffle_instance, 'storediffs')
    # print("  finished storing diffs")

    print("finished initialization!")

    initSouffleEnd = time.time()
    faultbase.logTime("initialize_souffle", initSouffleEnd - initSouffleStart)

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

    localize_start = time.time()
    result = set()
    if mode == 'localize':
        result = localize(souffle_instance, reverse_souffle_instance, faults, reverse_faults)
    elif mode == 'repair':
        result = repair(souffle_instance, reverse_souffle_instance, faults, reverse_faults)
    else:
        print("Mode is 'localize' or 'repair'")

    localize_end = time.time()
    faultbase.logTime("localize_repair_faults", localize_end - localize_start)

    print(result)

    # Enable user interaction - the user can specify some set of tuples to
    # exclude from the given result
    if allow_user_interaction:
        while True:
            excluded_tuples = get_excluded_tuples()
            if len(excluded_tuples) == 0:
                break

            for t in excluded_tuples:
                for r in result:
                    if t.replace(" ", "") in r.replace(" ", ""):
                        if r.endswith("(-)"):
                            # this tuple was originally deleted from the diff, so we
                            # should insert into souffle_instance, and delete from
                            # reverse_souffle_instance
                            faultbase.execSouffleCmd(souffle_instance, 'insert ' + t)
                            faultbase.execSouffleCmd(reverse_souffle_instance, 'remove ' + t)

                        elif r.endswith("(+)"):
                            faultbase.execSouffleCmd(souffle_instance, 'remove ' + t)
                            faultbase.execSouffleCmd(reverse_souffle_instance, 'insert ' + t)

                        break

            faultbase.execSouffleCmd(souffle_instance, 'commit')
            faultbase.execSouffleCmd(reverse_souffle_instance, 'commit')

            # redo localization/repair!
            if mode == 'localize':
                result = localize(souffle_instance, reverse_souffle_instance, faults, reverse_faults)
            elif mode == 'repair':
                result = repair(souffle_instance, reverse_souffle_instance, faults, reverse_faults)

    return result

if __name__ == '__main__':
    result = main()
    print(result, len(result))
