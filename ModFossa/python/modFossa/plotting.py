from globals import *
import matplotlib as mpl
import matplotlib.pyplot as plt
from itertools import cycle

import results

#### Plotting ####
def plotStates(experimentSweepName):
    plotData = getStateProbabilities(experimentSweepName)
    names = getStateNames()

    fig = plt.figure(figsize=(8, 5), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)

    style = cycle(['r-', 'b--', 'g-.'])
    states = []
    
    numStates = len(plotData[0][0])
    for n in range(numStates):
        states.append([])

    for time in plotData[0]:
        for i, state in enumerate(time):
            states[i].append(state)

    for state in states:
        ax.plot(state, next(style), linewidth=2)

    leg = ax.legend(names, 'center right', shadow=True)
    ax.set_xlabel('Time (ms)')
    ax.set_ylabel('Probability')
    
    plt.show()
    return fig

def plotVoltageProtocol(experimentSweepName):
    fig = plt.figure(figsize=(8, 4), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)
    plotData = results.getVoltageProtocol(experimentSweepName)
    
    for iteration in plotData:
        plt.plot(iteration, color='black', linewidth=0.5)

    # Make x and y ticklabels smaller 
    for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
    for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
    mpl.rcParams['axes.linewidth'] = 0.8 
    ax.set_xlabel('time (ms)')
    ax.set_ylabel('V (mV)')
    ax.minorticks_on()

    plt.show()
    return fig

def plotMultipleCurrents(sweeps, prefix):
    fig = plt.figure(figsize=(10, 10), facecolor='w', edgecolor='k') 
    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        plotData = results.getCurrents(name)
        ax = fig.add_subplot(len(sweeps)/2, 2, i + 1)
        for currentTrace in plotData:
            plt.plot(currentTrace, color='black', linewidth=0.5)

        # Make x and y ticklabels smaller 
        for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
        for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
        mpl.rcParams['axes.linewidth'] = 0.8 
        ax.set_xlabel('time (ms)')
        ax.set_ylabel('I (pA)')        
        plt.ylim(-30, 50)
        plt.text(100, 40, str(sweep) + 'nM [Ca]i')

    plt.show()
    return fig


def plotCurrentsSingleColumn(sweeps, prefix):
    fig = plt.figure(figsize=(4,10), facecolor='w', edgecolor='k') 
    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        plotData = results.getCurrents(name)
        ax = fig.add_subplot(len(sweeps) + 1, 1, i + 1)
        for currentTrace in plotData:
            plt.plot(currentTrace, color='black', linewidth=0.5)

        ax.set_axis_off()
        plt.ylim(-30, 50)
        plt.text(0, 50, str(sweep) + 'nM [Ca]i', fontsize=10)


    ## Plot voltage protocol at bottom
    ax = fig.add_subplot(len(sweeps) + 1, 1, len(sweeps) + 1)
    plotData = results.getVoltageProtocol(prefix + str(sweeps[0]))
    
    for iteration in plotData:
        plt.plot(iteration, color='black', linewidth=0.8)

    ax.set_axis_off()    

    plt.show()
    return fig    


def plotMultipleIV(sweeps, prefix, time_ms, ymin, ymax, labelheight):
    fig = plt.figure(figsize=(10,10), facecolor='w', edgecolor='k') 
    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        plotData = results.getIV(name, time_ms)
        ax = fig.add_subplot(len(sweeps)/2, 2, i + 1)
        plt.plot(plotData[0], plotData[1], color='red', linewidth=3, marker='o',
            markerfacecolor='red', markersize=7)

        # Make x and y ticklabels smaller 
        for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
        for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
        mpl.rcParams['axes.linewidth'] = 0.8 
        ax.set_xlabel('V (mV)')
        ax.set_ylabel('I (pA/pF)')
        #ax.set_title(name)
        ax.minorticks_on()
        ax.set_xticks([-100, -60, -20, 20, 60, 100, 140])
        plt.ylim(ymin, ymax)
        plt.xlim(xmin=-110)
        plt.text(-100, labelheight, str(sweep) + 'nM [Ca]i')

    plt.show()
    return fig


def plotIV(experimentSweepName, time_ms):
    plotData = getIV(experimentSweepName, time_ms)
    
    #fig = plt.figure(1)
    fig = plt.figure(figsize=(4,3), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)
    ax.plot(plotData[0], plotData[1], color='red', linewidth=3, marker='o',
        markerfacecolor='red', markersize=7)

    #leg = ax.legend(names, 'center right', shadow=True)
    # Make x and y ticklabels smaller 
    for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
    for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
    mpl.rcParams['axes.linewidth'] = 0.8 
    ax.set_xlabel('V (mV)')
    ax.set_ylabel('I (pA/pF)')
    ax.set_title('IV')
    #ax.minorticks_on()
    ax.set_xticks(plotData[0])
    #ax.autoscale_view(True,True,True)
    plt.xlim(xmin=-110)
    plt.show()
    return fig

def plotCurrents(experimentSweepName):
    plotData = getCurrents(experimentSweepName)

    fig = plt.figure(figsize=(6,4), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)
    for currentTrace in plotData:
        ax.plot(currentTrace, 'k', linewidth=0.5)

    for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
    for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
    mpl.rcParams['axes.linewidth'] = 0.8 
    ax.set_xlabel('Time (ms)')
    ax.set_ylabel('I (pA)')
    fig.tight_layout()
    plt.show()
    return fig

def plot(plotData):
    fig = plt.figure(1)
    ax = fig.add_subplot(111)

    for iteration in plotData:
        ax.plot(iteration, 'b')

    leg = ax.legend(('C1', 'C2', 'O'), 'center right', shadow=True)
    ax.set_xlabel('Time (ms)')
    ax.set_ylabel('Probability')
    ax.set_title('Channel Probability')
    ax.autoscale_view(True,True,True)
    plt.axis([0, 2000, -100, 200])
    
    plt.show()

def plotGvsCa(sweeps, prefix, time):
    fig = plt.figure(figsize=(6, 4), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)

    # First, get number of voltages that we have, N.
    # We will create N lists to plot.
    conductances = results.getConductances(prefix + str(sweeps[0]))
    gAtVoltages=[]

    for i in range(len(conductances)):
        gAtVoltages.append([])

    for i in range(len(gAtVoltages)):
        gAtVoltages[i].append([])
        gAtVoltages[i].append([])

    for sweep in sweeps:
        name = prefix + str(sweep)

        conductances = results.getConductances(name)
        for i, iteration_conductance in enumerate(conductances):
            gAtVoltages[i][0].append(sweep)
            gAtVoltages[i][1].append(iteration_conductance[time])

    for gAtVoltage in gAtVoltages:
        plt.plot(gAtVoltage[0], gAtVoltage[1], color='black', linewidth=1, marker='o', 
                markerfacecolor='black', markersize=1)
    # Make x and y ticklabels smaller 
    for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
    for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
    mpl.rcParams['axes.linewidth'] = 0.8 
    ax.set_xlabel('Ca[i] (nM)')
    ax.set_ylabel('Chord Conductance (nS/pF)')
    ax.minorticks_on()
    plt.xlim(xmax = 1100)
    plt.show()
    return fig

def plotGvsV(sweeps, prefix, time):
    fig = plt.figure(figsize=(6, 4), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)

    # First, get number of sweeps that we have, N.
    # We will create N lists to plot.
    gAtSweeps=[]

    for i in range(len(sweeps)):
        gAtSweeps.append([])

    for i in range(len(gAtSweeps)):
        gAtSweeps[i].append([])
        gAtSweeps[i].append([])

    voltageProtocol = results.getVoltageProtocol(prefix + str(sweeps[0]))

    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        conductances = results.getConductances(name)
        for j, iteration_conductance in enumerate(conductances):
            gAtSweeps[i][0].append(voltageProtocol[j][time])
            gAtSweeps[i][1].append(iteration_conductance[time])

    for gAtSweep in gAtSweeps:
        plt.plot(gAtSweep[0], gAtSweep[1], color='black', linewidth=1, marker='o', 
                markerfacecolor='black', markersize=1)
    # Make x and y ticklabels smaller 
    for tick in plt.gca().xaxis.get_major_ticks(): tick.label1.set_fontsize(10) 
    for tick in plt.gca().yaxis.get_major_ticks(): tick.label1.set_fontsize(10)
    mpl.rcParams['axes.linewidth'] = 0.8 
    ax.set_xlabel('V (mV)')
    ax.set_ylabel('Chord Conductance (nS/pF)')
    ax.minorticks_on()
    #plt.xlim(xmax = 1100)
    plt.show()
    return fig
