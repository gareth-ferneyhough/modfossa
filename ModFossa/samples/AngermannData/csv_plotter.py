import csv
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from itertools import cycle

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
	v2 = np.array([-100,-90,-80,-70,-60,-50,-40,-30,-20,20,30,40,50,60,70,80,90,100,110,120,130])
	g_1000 = np.array([0.03124,0.03154,0.03535,0.03675,0.04158,0.04374,0.04927,0.05345,0.06001,0.0631,0.10743,0.10307,0.11684,0.12601,0.1327,0.14615,0.17095,0.19305,0.21902,0.2461,0.26261,0.3081])
	g_750 = np.array([0.04179,0.04278,0.04452,0.04619,0.04821,0.05094,0.05577,0.05817,0.06245,0.06314,0.09461,0.10141,0.10908,0.12206,0.13393,0.14625,0.16395,0.18102,0.20225,0.22086,0.2449,0.27429])
	g_500 = np.array([0.01628,0.01682,0.01889,0.02009,0.02309,0.02456,0.02561,0.02762,0.02615,0.02031, 0.07007,0.0751,0.08484,0.09724,0.10986,0.12575,0.14597,0.16578,0.19131,0.22224,0.25337,0.29976])
	g_250 = np.array([0.02181,0.02287,0.02274,0.02311,0.02426,0.0232,0.02532,0.02322,0.02264,0.03719,0.03934,0.04631,0.05233,0.06033,0.06732,0.07642,0.08901,0.10418,0.11916,0.14005,0.16492])
	g_100 = np.array([0.02389,0.02496,0.02585,0.02352,0.02397,0.02438,0.02353,0.02271,0.02469,0.02602,0.02779,0.02855,0.02777,0.02935,0.03092,0.03272,0.0335,0.03652,0.03675,0.0415,0.04441])
	g_20 = np.array([0.01213,0.011,0.00963,0.00954,0.00897,0.0078,0.00717,0.00849,0.00831,0.01682,0.01347,0.0131,0.01435,0.01352,0.01157,0.01401,0.01559,0.0168,0.01686,0.01941,0.02658])

	names = ['1000 nM Ca', '750 nM Ca', '500 nM Ca', '250 nM Ca', '100 nM Ca', '20 nM Ca']

	fig = plt.figure(figsize=(6,4), facecolor='w', edgecolor='k') 
	ax = fig.add_subplot(111)

	for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
	for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
	mpl.rcParams['axes.linewidth'] = 0.8 
	ax.set_xlabel('V (mV)')
	ax.set_ylabel('Chord Conductance (nS/pF)')
	ax.minorticks_on()

	style = cycle(['ks', 'kD', 'kv', 'k^', 'kp', 'k<'])

	handles = []
	handles.append(curveFit(v, g_1000, ax, next(style)))
	handles.append(curveFit(v, g_750, ax, next(style)))
	handles.append(curveFit(v, g_500, ax, next(style)))
	handles.append(curveFit(v2, g_250, ax, next(style)))
	handles.append(curveFit(v2, g_100, ax, next(style)))
	handles.append(curveFit(v2, g_20, ax, next(style)))


	ax.legend(handles, names, 'upper left', shadow=True)
	plt.xlim(-110, 150)

	plt.show()
	fig.savefig('../../results/' + 'angermann_g_vs_v_atp_experimental.eps', format='eps')

def curveFit(x, y, ax, style):

	popt, pcov = curve_fit(func, x, y, p0=[200, -100, 100])

	xx = np.linspace(-100, 130)
	fitted = func(xx, popt[0], popt[1], popt[2])

	ax.plot(xx, fitted, color='black', linewidth=2)
	retval, = ax.plot(x, y, style)

	return retval

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