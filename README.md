# Fault Localization and Repair for Souffle programs

These scripts utilize Souffle's provenance functionality to automatically
localize and repair faults that result from incremental evaluation. For example,
an incremental update may result in some unwanted tuple _t_. Then, we wish to
either _localize_ (i.e., find some subset of the update that reproduces the
fault), or _repair_ (i.e., find some subset of the update that removes the
fault).

This repository depends on the incremental branch of Souffle, found here: <https://github.com/taipan-snake/souffle/tree/incremental-with-provenance-eager-diffs>

### Fault localization

The main script is in `fault-localize.py`. The script takes one argument: the
problem directory. In the problem directory, we expect to have the following:

```
problem_dir
|- query        # the executable generated and compiled by incremental souffle
|- update.in    # the update file diff, in the format that would usually be piped into the incremental CLI
|- faults.txt   # a list of fault tuples, each prepended by either `existing` or `missing`
|- facts        # a folder containing all input fact files
    |- <relation>.facts
```

See `tests/path` for an example. Running the script produces a subset of the
diff that localizes the fault:

```
$ python3 fault-localize.py tests/path
{'unwanted_edge(1, 3) (+)', 'unwanted_edge(2, 3) (-)'}
```

### Fault repair

The fault repair script functions in much the same way as the fault localization
script. It expects the same set of files in the problem directory, and is
executed the same way.

The result of the repair script is a set of tuples that potentially repairs the
faults, i.e., if those tuples are removed from the diff, then the faults
disappear.
