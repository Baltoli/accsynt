#!/usr/bin/env python

import graphviz
import random
import sys

import numpy as np
import pandas as pd

from sklearn.model_selection import LeaveOneOut, train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn_porter import Porter

def input_vars(df):
    return [cn for cn in df.columns if not cn.startswith('out')]

def output_vars(df):
    return [cn for cn in df.columns if cn.startswith('out')]

def input_data(df):
    return df.loc[:, input_vars(df)]

def output_var(df, var):
    return df.loc[:, var]

def model(seed):
    forest = RandomForestClassifier(n_estimators=20, max_depth=8, random_state=seed)
    return forest

def seeds():
    return [2513, 3838, 1722, 1901, 1609]

def main(argv):
    path = argv[0]
    data = pd.read_csv(path)

    mode = argv[1]
    if mode not in ['stats', 'code']:
        print('Invalid mode: {}'.format(mode))
        sys.exit(1)

    e_vars = argv[2:]

    if mode == 'code' and len(e_vars) != 1:
        print('Can only export code for one model')
        sys.exit(2)

    if len(e_vars) == 0:
        e_vars = output_vars(data)

    for var in e_vars:
        xs, ys = input_data(data), output_var(data, var)

        accs = []
        for s in seeds():
            train_xs, test_xs, train_ys, test_ys = train_test_split(
                xs, ys, test_size=0.25, random_state=s)

            mod = model(s).fit(train_xs, train_ys)
            accs.append(np.sum(mod.predict(test_xs) == test_ys) / float(len(test_ys)))

        if mode == 'stats':
            print("{}: {:.2f}%".format(var, 100 * sum(accs) / len(accs)))

        if mode == 'code':
            func_name = 'predict_{}'.format(var)

            port = Porter(mod, language='c')
            code = port.export(embed_data=True)
            code = code.replace('int predict_', 'static int predict_')
            code = code.replace('predict', func_name)
            code = "\n".join(code.split('\n')[:-10])

            print(code, file=sys.stdout)

            header_line = 'extern "C" int {} (float features[]);'.format(func_name);
            print(header_line, file=sys.stderr)

if __name__ == "__main__":
    main(sys.argv[1:])
