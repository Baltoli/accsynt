#!/usr/bin/env python

import pandas as pd
import sys

if __name__ == "__main__":
    df = pd.read_csv(sys.argv[1], names=['instruction', 'function'])
    # df = df[df['function'] != 'disable_trace']
    df['freq'] = df.groupby('instruction')['instruction'].transform('count')
    df = df.drop_duplicates().reset_index(drop=True)
    print(df.to_csv(index=False))
