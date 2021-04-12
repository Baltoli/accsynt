#!/usr/bin/env python

import groups
import pandas as pd
import sys

bad_funcs = [
    'disable_trace',
    'trace_enabled'
]

if __name__ == "__main__":
    dfs = [pd.read_csv(in_f) for in_f in sys.argv[1:]]
    df = pd.concat(dfs)
    df = df[~df['function'].isin(bad_funcs)].dropna()
    df['group'] = df['function'].apply(groups.lookup)
    print(df.to_csv(index=False))
