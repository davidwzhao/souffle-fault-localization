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

def delta_debugging(faults, missing_faults, updates):
    global problem_dir

    divisions = 2

    current_updates = updates

    num_iterations = 0

    while True:
        num_iterations += 1
        for diff_subset in breakIntoPieces(current_updates, divisions):
            # apply the current diff
            delta_debugging_base.applyDiffToInput(problem_dir, diff_subset, "facts", "facts_current")
            delta_debugging_base.initSouffle(problem_dir, "query-batch", "facts_current")

            bug_reproduced = True

            for rel in faults.keys():
                if not delta_debugging_base.tuplesInRelation(os.path.join(problem_dir, rel + '.csv'), faults[rel]):
                    bug_reproduced = False
                    break

            for rel in missing_faults.keys():
                if delta_debugging_base.tuplesInRelation(os.path.join(problem_dir, rel + '.csv'), missing_faults[rel]):
                    bug_reproduced = False
                    break

            # take the smaller subset
            if bug_reproduced:
                current_updates = diff_subset

        if divisions == len(current_updates):
            break
        divisions = min(len(current_updates), divisions * 2)
        if divisions == 0:
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

    print("faults:", faults)
    print("reverse faults:", reverse_faults)

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
