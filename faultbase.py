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

########################################################################################################################
# Tuple input/output utilities

# this applies a diff up to the first 'commit'
def applyDiffToInput(diffFilename, problemDirName, inputFactsFolder, outputFactsFolder):
    startTime = time.time()
    toInsert = collections.defaultdict(set)
    toDelete = collections.defaultdict(set)

    with open(os.path.join(problemDirName, diffFilename), 'r') as diffFile:
        for l in diffFile:
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
                    f_new.write(l)

        # os.rename(os.path.join(problemDirName, rel + '.facts.new'), os.path.join(problemDirName, rel + '.facts'))

    endTime = time.time()
    logTime('applyDiffToInput', endTime - startTime)

########################################################################################################################
# Souffle functions

def initIncSouffle(problemDirName, souffleExecName, factsFolder = 'facts'):
    # make a copy of all fact files to save as originals
    # for facts in [x for x in os.listdir(problemDirName) if x.endswith('.facts')]:
    #     shutil.copyfile(os.path.join(problemDirName, facts), os.path.join(problemDirName, facts + '.orig'))

    souffle = subprocess.Popen([ f'{problemDirName}/{souffleExecName}', '-F', os.path.join(problemDirName, factsFolder), '-D', problemDirName ], \
                               stdin=subprocess.PIPE, \
                               stdout=subprocess.PIPE, \
                               universal_newlines=True)

    while next(souffle.stdout).strip() != '###': pass
    while next(souffle.stdout).strip() != '###': pass

    execSouffleCmd(souffle, 'format json')
    execSouffleCmd(souffle, 'setdepth 10000')

    return souffle


# def initIncSouffle(problemDirName, souffleExecName, expectedOut, rPlus):
#     with open(f'{problemDirName}/Rule.facts', 'w') as outFile:
#         for name in rPlus: print(name, file=outFile)
# 
#     startTime = time.time()
#     souffle = subprocess.Popen([ f'{problemDirName}/{souffleExecName}', '-F', problemDirName, '-D', problemDirName ], \
#                                stdin=subprocess.PIPE, \
#                                stdout=subprocess.PIPE, \
#                                universal_newlines=True)
#     while next(souffle.stdout).strip() != '###': pass
#     while next(souffle.stdout).strip() != '###': pass
#     endTime = time.time()
#     logTime('souffleInit', endTime - startTime)
#     execSouffleCmd(souffle, 'format json')
#     tuplesProduced = { relName: loadRelation(f'{problemDirName}/{relName}.csv') for relName in expectedOut }
#     return (souffle, tuplesProduced)

def execSouffleCmd(souffle, cmd):
    startTime = time.time()
    print(cmd, file=souffle.stdin)
    souffle.stdin.flush()
    response = [ next(souffle.stdout).strip() ]
    while response[-1] != '###': response.append(next(souffle.stdout).strip())
    response = response[:-1]
    ans = '\n'.join(response)
    endTime = time.time()
    logTime('souffleCmd', endTime - startTime)
    return ans

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


########################################################################################################################
# Souffle provenance functions

def getOneProv(souffle, tupleStr):
    startTime = time.time()
    p = execSouffleCmd(souffle, 'explainall ' + tupleStr)
    p = json.loads(p)
    tuples = getOneTreeFromProvJson(p)

    endTime = time.time()
    logTime('getOneProv', endTime - startTime)

    return tuples

# def getOneProv(souffle, relName, t):
#     p = execSouffleCmd(souffle, 'explainall ' + printSouffleTuple(relName, t))
#     p = json.loads(p)
#     tuples = getOneTreeFromProvJson(p)
# 
#     return tuples

def isDiff(s):
    return s.endswith('(+)') or s.endswith('(-)')

def getOneTreeFromProvJson(provenance):
    provenance = provenance['proof']

    def getOneTreeFromProvJsonInt(p):
        # print(p)
        if 'axiom' in p:
            return [p['axiom']]
        elif 'children_0' in p:
            return functools.reduce((lambda x, y: x + y), [ getOneTreeFromProvJsonInt(child) for child in p['children_0'] ])

    res = getOneTreeFromProvJsonInt(provenance)

    # filter out only diff tuples
    res = list(filter(isDiff, res))

    return res

# def cleanProvenanceJson(provenance):
#     provenance = provenance['proof']
# 
#     def cleanProvenanceJsonInt(p):
#         if 'axiom' in p: return { 'axiom': p['axiom'] }
#         return { 'premises': p['premises'], \
#                  'children': [ cleanProvenanceJsonInt(child) for child in p['children_0'] ] }
# 
#     provenance = cleanProvenanceJsonInt(provenance)
#     return provenance

def squashDesirableConclusions(provenance, expectedOut):
    if 'axiom' in provenance: return provenance
    else:
        relName, t = probase.parseSouffleString(provenance['premises'])
        if relName in expectedOut and t in expectedOut[relName]:
            return { 'axiom': provenance['premises'] }
        else:
            return { 'premises': provenance['premises'], \
                     'children': [ squashDesirableConclusions(child, expectedOut) for child in provenance['children'] ] }

def collectRules(provenance):
    if 'axiom' in provenance:
        axiomRel, axiomT = probase.parseSouffleString(provenance['axiom'])
        if axiomRel == 'Rule': return frozenset([ axiomT[0] ])
        else: return frozenset()
    else:
        return frozenset({ ruleName for child in provenance['children'] \
                                    for ruleName in collectRules(child) })
