#!/usr/bin/env python3

import collections
import logging
import os
import sys

import delta_debugging_base

problem_dir = ""

def breakIntoPieces(l, numPieces):
    avg = len(l) / float(numPieces)
    out = []
    last = 0.0

    while last < len(l):
        out.append(l[int(last):int(last+avg)])
        last += avg

    return out

def is_bug_reproduced(faults, missing_faults):
    bug_reproduced = True

    for rel in faults.keys():
        rel_file = rel.replace("mainAnalysis_", "")
        if not delta_debugging_base.tuplesInRelation(os.path.join(problem_dir, "output_temp", rel_file + '.csv'), faults[rel]):
            bug_reproduced = False
            break

    for rel in missing_faults.keys():
        rel_file = rel.replace("mainAnalysis_", "")
        if delta_debugging_base.tuplesInRelation(os.path.join(problem_dir, "output_temp", rel_file + '.csv'), missing_faults[rel]):
            bug_reproduced = False
            break

    return bug_reproduced

def delta_debugging(faults, missing_faults, updates):
    global problem_dir

    divisions = 2

    current_updates = sorted(updates)

    num_iterations = 0

    while True:
        num_iterations += 1
        all_pass = True
        print("starting iteration", num_iterations)
        for diff_subset in breakIntoPieces(current_updates, divisions):
            # apply the current diff
            delta_debugging_base.applyDiffToInput(problem_dir, diff_subset, "facts", "facts_current")
            delta_debugging_base.initSouffle(problem_dir, "computation", "facts_current")

            bug_reproduced = is_bug_reproduced(faults, missing_faults)

            logging.debug("current subset: " + str(diff_subset) + ", bug_reproduced: " + str(bug_reproduced))

            # take the smaller subset
            if bug_reproduced:
                all_pass = False
                current_updates = diff_subset
                divisions = 2
                break

            # only check complements if more than 2 divisions, otherwise this is
            # handled by the normal check
            if divisions > 2:
                current_diff_subset = set(current_updates) - set(diff_subset)

                # apply the current diff
                delta_debugging_base.applyDiffToInput(problem_dir, current_diff_subset, "facts", "facts_current")
                delta_debugging_base.initSouffle(problem_dir, "computation", "facts_current")

                bug_reproduced = is_bug_reproduced(faults, missing_faults)

                logging.debug("current subset: " + str(current_diff_subset) + ", bug_reproduced: " + str(bug_reproduced))

                # take the smaller subset
                if bug_reproduced:
                    all_pass = False
                    current_updates = sorted(list(current_diff_subset))
                    divisions = divisions - 1
                    break

        if all_pass:
            divisions = divisions * 2

        if divisions > len(current_updates):
            break

    logging.info("delta debugging took " + str(num_iterations) + " iterations")

    return current_updates

def main():
    global problem_dir
    problem_dir = sys.argv[1]

    # get list of faults
    faults = collections.defaultdict(list)
    reverse_faults = collections.defaultdict(list)
    with open(os.path.join(problem_dir, 'faults.txt'), 'r') as faults_file:
        for l in faults_file:
            l = l.rstrip()

            (kind, tup) = tuple(l.split(' ', maxsplit=1))

            tup = delta_debugging_base.parseSouffleTuple(tup)

            if kind == 'existing':
                faults[tup[0]].append(tup[1])

            if kind == 'missing':
                reverse_faults[tup[0]].append(tup[1])

    print("faults:", faults, len(faults))
    print("reverse faults:", reverse_faults, len(reverse_faults))

    # get list of updates
    updates = []
    with open(os.path.join(problem_dir, 'update.in'), 'r') as updates_file:
        for l in updates_file:
            l = l.rstrip()

            if 'insert ' in l or 'remove ' in l:
                updates.append(l)

    return delta_debugging(faults, reverse_faults, updates)

if __name__ == '__main__':
    result = main()
    print(result, len(result))
