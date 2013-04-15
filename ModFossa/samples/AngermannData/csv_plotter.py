#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import csv
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def main():
	# filename = 'angermann_g_vs_v_atp.csv'
	# f = open(filename)
	# csvfile = csv.reader(f, delimiter=',')

	# A = np.array(map(float, csvfile.next()), ndmin=2)
	# for row in csvfile:
	# 	A = np.vstack([A, map(float, row)])



	# #print A[0][5]
	# B = A.astype(np.float).T

	# #print B
	# #plot(B)

	

	v = np.array([-100,-90,-80,-70,-60,-50,-40,-30,-20,-10,20,30,40,50,60,70,80,90,100,110,120,130])
	g_1000 = np.array([0.03124,0.03154,0.03535,0.03675,0.04158,0.04374,0.04927,0.05345,0.06001,0.0631,0.10743,0.10307,0.11684,0.12601,0.1327,0.14615,0.17095,0.19305,0.21902,0.2461,0.26261,0.3081])

	curveFit(v, g_1000)

def curveFit(x, y):

	popt, pcov = curve_fit(func, x, y, p0=[200, -100, 100])
	print popt

	xx = np.linspace(-100, 130)
	fitted = func(xx, popt[0], popt[1], popt[2])

	fig = plt.figure(figsize=(4,3), facecolor='w', edgecolor='k') 
	ax = fig.add_subplot(111)
	
	ax.plot(x, y)
	ax.plot(xx, fitted)
	
	plt.show()

def func(v, v_half, k, c):
	retval = (1.16 / (1 + np.exp((v - v_half)/ k)) + c)
	return retval

def plot(B):
    fig = plt.figure(figsize=(4,3), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)
    ax.plot(B[0], B[1], color='red', linewidth=3, marker='o',
        markerfacecolor='red', markersize=7)

    plt.show()

if __name__ == "__main__":
    main()