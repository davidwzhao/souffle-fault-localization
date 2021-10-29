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
def applyDiffToInput(problemDirName, diffFilename, inputFactsFolder, outputFactsFolder):
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
                    f_new.write(l + '\n')

        # os.rename(os.path.join(problemDirName, rel + '.facts.new'), os.path.join(problemDirName, rel + '.facts'))

    # copy all files that do not have a diff
    for file in os.listdir(os.path.join(problemDirName, inputFactsFolder)):
        if remove_suffix(file, '.facts') in toInsert.keys() | toDelete.keys():
            continue
        else:
            shutil.copyfile(os.path.join(problemDirName, inputFactsFolder, file), os.path.join(problemDirName, outputFactsFolder, file))

    endTime = time.time()
    logTime('applyDiffToInput', endTime - startTime)

# this reverses an incremental diff
def reverseDiff(problemDirName, diffFilename, outputDiffFilename):
    startTime = time.time()
    with open(os.path.join(problemDirName, diffFilename), 'r') as diffFile:
        with open(os.path.join(problemDirName, outputDiffFilename), 'w') as outputDiffFile:
            for l in diffFile:
                t = l.split(' ', maxsplit=1)

                if t[0] == 'remove' or t[0] == 'insert':
                    # insert becomes remove and vice versa
                    (command, tup) = tuple(t)

                    if command == 'remove':
                        outputDiffFile.write('insert ' + tup)
                    elif command == 'insert':
                        outputDiffFile.write('remove ' + tup)
                else:
                    outputDiffFile.write(l)

    endTime = time.time()
    logTime('reverseDiff', endTime - startTime)


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

def apply_update(souffle_instance, update_file):
    with open(update_file, 'r') as update_file:
        for l in update_file:
            l = l.rstrip()
            execSouffleCmd(souffle_instance, l)


########################################################################################################################
# Souffle provenance functions

def isDiff(s):
    return s.endswith('(+)') or s.endswith('(-)')

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

def getAllProv(souffle, tupleStr):
    startTime = time.time()
    p = execSouffleCmd(souffle, 'explainall ' + tupleStr)
    p = json.loads(p)
    tuples = getAllTreesFromProvJson(p)

    endTime = time.time()
    logTime('getAllProv', endTime - startTime)

    return tuples

def getAllTreesFromProvJson(provenance):
    provenance = provenance['proof']
    allTrees = []

    def getAllTreesFromProvJsonInt(p):
        if 'axiom' in p:
            if isDiff(p['axiom']):
                return sympy.Symbol(p['axiom'])
            else:
                return None

        # go through alternative children
        cNum = 0

        currentFormula = False

        while 'children_' + str(cNum) in p:
            c = 'children_' + str(cNum)

            currentChildFormula = True
            for child in p[c]:
                childResult = getAllTreesFromProvJsonInt(child)

                if childResult != None:
                    currentChildFormula = currentChildFormula & childResult

            if currentChildFormula != True:
                currentFormula = currentFormula | currentChildFormula

            cNum += 1

        # print("current formula: ", currentFormula)

        return currentFormula

    def clauses(expr):    # for DNFs only
        if not isinstance(expr, sympy.logic.boolalg.Or):
            return [expr]
        return list(expr.args)

    treesFormula = getAllTreesFromProvJsonInt(provenance)

    if treesFormula == None:
        return []

    treesFormula = sympy.logic.to_dnf(treesFormula)

    for c in clauses(treesFormula):
        if isinstance(c, sympy.core.symbol.Symbol):
            allTrees.append([str(c)])
        elif c != None:
            allTrees.append(list(map(str, c.args)))

    return allTrees

    # def getAllTreesFromProvJsonInt(p, so_far):
    #     if 'axiom' in p:
    #         # we are at a leaf, add all the EDB tuples in the tree thus far
    #         allTrees.append(list(filter(isDiff, so_far)))

    #     childNum = 0

    #     while 'children_' + str(childNum) in p:
    #         c = 'children_' + str(childNum)

    #         axioms = []

    #         # if the current node has premises, we are not at a leaf
    #         hasPremises = False
    #         for child in p[c]:
    #             if 'axiom' in child:
    #                 axioms.append(child['axiom'])
    #             if 'premises' in child:
    #                 hasPremises = True

    #         if not hasPremises and len(p[c]) > 0:
    #             # just want to go to the first axiom
    #             getAllTreesFromProvJsonInt(p[c][0], so_far + axioms)

    #         for child in p[c]:
    #             if 'axiom' in child:
    #                 continue
    #             getAllTreesFromProvJsonInt(child, so_far + axioms)

    #         childNum += 1

    # getAllTreesFromProvJsonInt(provenance, [])

    # return allTrees

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

########################################################################################################################
# Various tuple processing functions

def remove_diff_suffix(t):
    t = remove_suffix(t, ' (-)')
    t = remove_suffix(t, ' (+)')
    return t

def flip_insert_remove(t):
    res = t
    if t.endswith("(-)") or t.endswith("(+)"):
        if t[-2] == '+':
            res = t[:-2] + '-)'
        elif t[-2] == '-':
            res = t[:-2] + '+)'

    return res
