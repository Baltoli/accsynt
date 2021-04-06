#!/usr/bin/env python3

import numpy as np
import pandas as pd
import scipy.optimize as opt
import sys

def const(x, cst):
    return cst

def linear(x, lin):
    return lin * x

def square(x, coef):
    return coef * (x ** 2)

def log(x, coef):
    return coef * np.log(x + 0.0001)

if __name__ == "__main__":
    df = pd.read_csv(sys.argv[1])
    df = df.groupby(['tag', 'param', 'value']).\
            agg({'time': 'mean'}).\
            reset_index()

    for (func, param), g in df.groupby(['tag', 'param']):
        for model in [const, linear, square, log]:
            popt, pcov = opt.curve_fit(model, g['value'], g['time'])
            residuals = g['time'] - model(g['value'], *popt)
            ss_res = np.sum(residuals**2)
            ss_tot = np.sum((g['time']-np.mean(g['value']))**2)
            r_squared = 1 - (ss_res / ss_tot)
            print(model, r_squared)
