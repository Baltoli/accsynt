#!/usr/bin/env python3

import pandas as pd
import sys

import groups

if __name__ == "__main__":
    ns = pd.read_csv(sys.argv[1])
    cs = pd.read_csv(sys.argv[2])
    assert(ns.size == cs.size)

    df = pd.concat([ns, cs], axis=1)
    df = df[df['candidates'] != -1]
    df['group'] = df['function'].apply(groups.lookup)
    
    print(df.to_csv(index=False))
