#!/usr/bin/env python3

import numpy as np
import pandas as pd
import scipy.optimize as opt
import sys

class Const:
    def __repr__(self):
        return "const"

    def __call__(self, x, cst):
        return cst

class Linear:
    def __repr__(self):
        return "linear"

    def __call__(self, x, lin):
        return lin * x

class Polynomial:
    def __init__(self, exp):
        self.exp = exp

    def __repr__(self):
        return f"poly({self.exp})"

    def __call__(self, x, coef):
        return coef * (x ** self.exp)

class Log:
    def __init__(self, base):
        self.base = base

    def __repr__(self):
        return f"log({self.exp})"

    def __call__(self, x, coef):
        return coef * np.log(x + 0.0001)

def fit_r_squared(model, xs, ys):
    popt, pcov = opt.curve_fit(model, xs, ys)
    residuals = ys - model(xs, *popt)
    ss_res = np.sum(residuals**2)
    ss_tot = np.sum((ys - np.mean(xs))**2)
    r_squared = 1 - (ss_res / ss_tot)
    return (popt, r_squared, model)

if __name__ == "__main__":
    df = pd.read_csv(sys.argv[1])
    df = df.groupby(['tag', 'param', 'value']).\
            agg({'time': 'mean'}).\
            reset_index()

    print("function,param,model")

    for (func, param), g in df.groupby(['tag', 'param']):
        models = [
            Const(), 
            Linear(),
            Polynomial(2),
            Log(2)
        ]

        scores = [fit_r_squared(m, g['value'], g['time']) for m in models]
        best = max(scores, key=lambda s: s[1])
        print(f"{func},{param},{best[2]}")
