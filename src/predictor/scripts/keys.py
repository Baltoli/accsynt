#!/usr/bin/env python

import sys

import numpy as np
import pandas as pd

def input_vars(df):
    return [cn for cn in df.columns if not cn.startswith('out')]

def main(argv):
    path = argv[0]
    data = pd.read_csv(path)

    vs = input_vars(data)
    code = "char const* keys[] = {\n  "
    strings = ",\n  ".join(['"{}"'.format(v) for v in vs])
    end = "\n}};\nint n_keys={};".format(len(vs))
    print(code + strings + end, file=sys.stdout)

    header = 'extern "C" char const* keys[];\nextern "C" int n_keys;'
    print(header, file=sys.stderr)

if __name__ == "__main__":
    main(sys.argv[1:])
