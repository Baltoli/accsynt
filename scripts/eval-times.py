#!/usr/bin/env python

import groups
import pandas as pd
import sys

if __name__ == "__main__":
    df = pd.read_csv(sys.argv[1])
    df['group'] = df['tag'].apply(groups.lookup)
    print(df.to_csv(index=False))
