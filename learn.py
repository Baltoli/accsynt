#!/usr/bin/env python

import graphviz
import random
from sklearn import tree

DATA = './dataset.txt'

def load_data():
    ret = []
    with open(DATA, 'r') as f:
        for line in f:
            ins, outs = line.split(' ')
            ins = [int(x) for x in ins.split(',')]
            outs = [int(x) for x in outs.split(',')]
            ret.append((ins, outs))
    return ret

def err(real, pred):
    s = 0
    for r, p in zip(real, pred):
        s += (r == p)
    return 1 - (float(s) / len(real))

def split(data, test = 0.1):
    copy = data[:]
    random.shuffle(copy)
    n_test = int(test * len(data))
    return copy[:n_test], copy[n_test:] 

def xs(data):
    return [p[0] for p in data]

def ys(data):
    return [p[1] for p in data]

def main():
    data = load_data()
    train, test = split(data)
    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(xs(train), ys(train))
    print(clf.predict_proba([xs(test)[1]]))

if __name__ == "__main__":
    main()
