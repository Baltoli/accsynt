#!/usr/bin/env python

import groups
import pandas as pd
import sys

bad_funcs = [
    'disable_trace',
    'trace_enabled'
]

bad_instrs = [
    'branch',
    'call',
    'return'
]

if __name__ == "__main__":
    dfs = [pd.read_csv(in_f) for in_f in sys.argv[1:]]
    df = pd.concat(dfs)
    df = df[~df['function'].isin(bad_funcs)].dropna()
    df = df[~df['instruction'].isin(bad_instrs)]
    df['group'] = df['function'].apply(groups.lookup)

    totals = {}
    for f, gr in df.groupby('function'):
        totals[f] = gr['freq'].sum()

    df['total'] = df.apply(lambda r: totals[r['function']], axis=1)
    df['rel_freq'] = df['freq'] / df['total']
    print(df.to_csv(index=False))
