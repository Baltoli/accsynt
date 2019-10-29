#!/usr/bin/env python

import graphviz
import random
import sys
from sklearn import tree

def load_data(path):
    ret = []
    with open(path, 'r') as f:
        for line in f:
            ins, outs = line.split(' ')
            ins = [int(x) for x in ins.split(',')]
            outs = int(outs)
            ret.append((ins, outs))
    return ret

def xs(data):
    return [p[0] for p in data]

def ys(data):
    return [p[1] for p in data]

def loo_splits(data):
    for i in range(len(data)):
        yield data[i], data[:i] + data[i+1:]

def main(argv):
    data = load_data(argv[0])
    correct = 0.0
    for test, train in loo_splits(data):
        clf = tree.DecisionTreeClassifier(random_state=0)
        clf = clf.fit(xs(train), ys(train))
        pred = clf.predict([test[0]])[0]
        if pred == test[1]:
            correct += 1
    print("LOO-CV Accuracy on {}: {:.2f}%".format(
        argv[0], 
        100 * correct / len(data)
    ))

if __name__ == "__main__":
    main(sys.argv[1:])
