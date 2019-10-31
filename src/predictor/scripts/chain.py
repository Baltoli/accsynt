#!/usr/bin/env python

import graphviz
import random
import sys

import numpy as np
import pandas as pd

from sklearn.model_selection import LeaveOneOut, train_test_split
from sklearn.multioutput import ClassifierChain
from sklearn.ensemble import RandomForestClassifier
from sklearn_porter import Porter

def input_vars(df):
    return [cn for cn in df.columns if not cn.startswith('out')]

def output_vars(df):
    return ['out_num_props', 'out_num_outputs', 'out_num_sizes']

def input_data(df):
    return df.loc[:, input_vars(df)]

def output_data(df):
    return df.loc[:, output_vars(df)]

def model(seed):
    forest = RandomForestClassifier(n_estimators=20, max_depth=5, random_state=seed)
    return forest

def chain(seed):
    return ClassifierChain(model(seed))

def seeds():
    return [2513, 3838, 1722, 1901, 1609]

def main(argv):
    path = argv[0]
    data = pd.read_csv(path)

    xs, ys = input_data(data), output_data(data)
    for s in seeds():
        train_xs, test_xs, train_ys, test_ys = train_test_split(
            xs, ys, test_size=0.25, random_state=s)

        mod = chain(s).fit(train_xs, train_ys)
        print(np.sum(mod.predict(test_xs) == test_ys))

    # e_vars = argv[1:]
    # if len(e_vars) == 0:
    #     e_vars = output_vars(data)

    # for var in e_vars:
    #     xs, ys = input_data(data), output_var(data, var)

    #     accs = []

    #         mod = model(s).fit(train_xs, train_ys)
    #         accs.append(np.sum(mod.predict(test_xs) == test_ys) / float(len(test_ys)))

    #     print("{}: {:.2f}%".format(var, 100 * sum(accs) / len(accs)))

        # port = Porter(model().fit(xs, ys), language='c')
        # print(port.export(embed_data=True))

if __name__ == "__main__":
    main(sys.argv[1:])
