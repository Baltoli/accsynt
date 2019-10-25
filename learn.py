#!/usr/bin/env python

import graphviz
from sklearn import tree

# A,B,V = 0, 1, 2
# ptr = 0, 1
# out = 1 if V A0 B1

A, B, V = 0, 1, 2

def main():
    X = [
        [V, 0, A, 0, B, 1],
        [A, 1, A, 1, A, 1],
        [B, 0, B, 0, B, 1],
        [V, 1, A, 0, B, 1],
        [V, 0, B, 1, A, 0]
    ]
    Y = [1, 0, 0, 0, 1]

    clf = tree.DecisionTreeClassifier()
    clf = clf.fit(X, Y)

    dot_data = tree.export_graphviz(clf, out_file=None)
    graph = graphviz.Source(dot_data)
    graph.render('outf')

if __name__ == "__main__":
    main()
