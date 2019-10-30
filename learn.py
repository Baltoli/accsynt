#!/usr/bin/env python

import graphviz
import random
import sys
import pandas as pd
from sklearn import svm

def output_vars(df):
    return [cn for cn in df.columns if cn.startswith('out')]

def input_vars(df):
    return [cn for cn in df.columns if not cn.startswith('out')]

def split(data):
    return data.loc[:, input_vars(data)], data.loc[:, output_vars(data)]

def main(argv):
    data = pd.read_csv(argv[0])
    data = data.sample(frac=1).reset_index(drop=True)
    train, test = data.loc[:90], data.loc[91:]
    xs, ys = split(train)
    clf = svm.SVC(gamma='scale')
    clf = clf.fit(xs, ys.values.ravel())
    txs, tys = split(test)
    print(clf.predict(txs))
    print(tys.values.ravel())

if __name__ == "__main__":
    main(sys.argv[1:])
