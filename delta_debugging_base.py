#!/usr/bin/python3

# This contains all the basic functions needed to run incremental souffle, pass
# input and get output.

import collections
import functools
import json
import logging
import os
import re
import shutil
import subprocess
import sympy
import time

########################################################################################################################
# 1a. Logging

logging.basicConfig(level=logging.INFO, \
                    format="[%(asctime)s] %(levelname)s [%(module)s.%(funcName)s:%(lineno)d] %(message)s", \
                    datefmt="%H:%M:%S")

# 1b. Timers

scriptStartTime = time.time()
Timer = collections.namedtuple('Timer', ['numCalls', 'time'])
timers = {}

def logTime(name, t):
    if name not in timers: timers[name] = Timer(0, 0)
    numCalls, prevTime = timers[name]
    timers[name] = Timer(numCalls + 1, prevTime + t)

def getTimer(name):
    if name not in timers: timers[name] = Timer(0, 0)
    return timers[name]

def printTimers():
    logTime('script', time.time() - scriptStartTime)
    logging.info('--- Timers ---')
    for k, (vn, vt) in sorted(timers.items(), key=lambda kv: kv[1].time):
        logging.info(f'{k}: {vt} seconds, {vn} calls')

import atexit
atexit.register(printTimers)

def remove_suffix(self: str, suffix: str) -> str:
    # suffix='' should not call self[:-0].
    if suffix and self.endswith(suffix):
        return self[:-len(suffix)]
    else:
        return self[:]

########################################################################################################################
# Tuple input/output utilities

# this applies a diff up to the first 'commit'
def applyDiffToInput(problemDirName, diffs, inputFactsFolder, outputFactsFolder):
    startTime = time.time()
    toInsert = collections.defaultdict(set)
    toDelete = collections.defaultdict(set)

    # with open(os.path.join(problemDirName, diffFilename), 'r') as diffFile:
    #     for l in diffFile:
    #         l = l.rstrip()

    #         if l == 'commit':
    #             break

    #         (command, tup) = tuple(l.split(' ', maxsplit=1))
    #         tup = parseSouffleTuple(tup)

    #         # create tab-separated version of tuple and insert into appropriate
    #         # set
    #         if command == 'remove':
    #             toDelete[tup[0]].add("\t".join(tup[1]))
    #         elif command == 'insert':
    #             toInsert[tup[0]].add("\t".join(tup[1]))

    for l in diffs:
        l = l.rstrip()

        if l == 'commit':
            break

        (command, tup) = tuple(l.split(' ', maxsplit=1))
        tup = parseSouffleTuple(tup)

        # create tab-separated version of tuple and insert into appropriate
        # set
        if command == 'remove':
            toDelete[tup[0]].add("\t".join(tup[1]))
        elif command == 'insert':
            toInsert[tup[0]].add("\t".join(tup[1]))

    os.makedirs(os.path.join(problemDirName, outputFactsFolder), exist_ok=True)

    # go through each fact file and insert/delete as appropriate
    for rel in toInsert.keys() | toDelete.keys():
        with open(os.path.join(problemDirName, inputFactsFolder, rel + '.facts'), 'r') as f:
            with open(os.path.join(problemDirName, outputFactsFolder, rel + '.facts'), 'w') as f_new:
                for l in f:
                    if l.rstrip() in toDelete[rel]:
                        continue
                    f_new.write(l)

                for l in toInsert[rel]:
                    f_new.write(l + '\n')

        # os.rename(os.path.join(problemDirName, rel + '.facts.new'), os.path.join(problemDirName, rel + '.facts'))

    # copy all files that do not have a diff
    for file in os.listdir(os.path.join(problemDirName, inputFactsFolder)):
        if file.endswith('.facts'):
            if remove_suffix(file, '.facts') in toInsert.keys() | toDelete.keys():
                continue
            else:
                shutil.copyfile(os.path.join(problemDirName, inputFactsFolder, file), os.path.join(problemDirName, outputFactsFolder, file))

    endTime = time.time()
    # logTime('applyDiffToInput', endTime - startTime)

# this loads a relation from a tab-separated .csv file
def loadRelation(filename):
    ans = { line.strip() for line in open(filename) if line.strip() }
    ans = { tuple(line.split('\t')) for line in ans }
    return ans

# check if a tuple exists in a relation
def tuplesInRelation(filename, tups):
    with open(filename, 'r') as f:
        for line in f:
            line = line.rstrip()
            tup = tuple(line.split('\t'))
            if tup in tups:
                return True

    return False

########################################################################################################################
# Souffle functions

def initSouffle(problemDirName, souffleExecName, factsFolder = 'facts'):
    # make a copy of all fact files to save as originals
    # for facts in [x for x in os.listdir(problemDirName) if x.endswith('.facts')]:
    #     shutil.copyfile(os.path.join(problemDirName, facts), os.path.join(problemDirName, facts + '.orig'))

    souffle = subprocess.Popen([ f'{problemDirName}/{souffleExecName}', '-F', os.path.join(problemDirName, factsFolder), '-D', problemDirName ], \
                               stdin=subprocess.PIPE, \
                               stdout=subprocess.PIPE, \
                               universal_newlines=True)

def printSouffleTuple(relName, t):
    t = tuple( f'"{x}"' for x in t )
    t = ', '.join(t)
    return '{}({})'.format(relName, t)

def parseSouffleTuple(string):
    startTime = time.time()
    xs = string.split('(')
    relName, xs = [ x.strip() for x in xs ]
    xs = xs.split(')')[0].strip()
    xs = [ x.strip() for x in xs.split(',') ]
    xs = tuple([ x[1:-1].strip() if x.startswith('"') and x.endswith('"') else x for x in xs ])
    ans = (relName, xs)
    endTime = time.time()
    return ans
