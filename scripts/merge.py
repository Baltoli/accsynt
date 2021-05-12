#!/usr/bin/env python

import argparse
import pandas as pd
import sys

def get_args():
    parser = argparse.ArgumentParser(description='Merge datasets')
    parser.add_argument('inputs', type=str, nargs='+',
                        help='Input files')
    parser.add_argument('--output', type=str, default='-',
                        help='Output file')
    return parser.parse_args()

if __name__ == "__main__":
    args = get_args()
    dfs = [pd.read_csv(in_f) for in_f in args.inputs]
    merged = pd.concat(dfs)
    merged.to_csv(sys.stdout if args.output == '-' else args.output, index=False)
