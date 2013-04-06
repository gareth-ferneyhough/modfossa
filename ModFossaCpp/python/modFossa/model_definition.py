import ModFossa
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
#class modFossa:
    
  #  def __init__():
simulationRunner = ModFossa.simulationRunner()
results = simulationRunner.results()
experiment = simulationRunner.experiment()
markovModel = experiment.markovModel()


def state(name, conducting = False, gating = 1.0):
    try: state = ModFossa.state(name, conducting, gating)
    except RuntimeError, e:
        print e

    try:
        markovModel.addState(state)
    except RuntimeError, e:
        print e

def rate(name, **args):
    if args['type'] == 'constant':
        _addConstantRateConstant(name, **args)
    elif args['type'] == 'sigmoidal':
        _addSigmoidalRateConstant(name, **args)
    elif args['type'] == 'ligandGated':
        _addLigandGatedRateConstant(name, **args)
    elif args['type'] == 'boltzman':
        print 'boltzman'
    elif args['type'] == 'exponential':
        _addExponentialRateConstant(name, **args)

def connect(**args):
    if len(args) != 3:
        print 'Incorrent number of arguments to connect'

    if not 'from_state' in args:
        raise RuntimeError("argument \'from_state\' not found when adding "
                            "connection")

    if not 'to_state' in args:
        raise RuntimeError("argument \'to_state\' not found when adding "
                            "connection")

    if not 'rate' in args:
        raise RuntimeError("argument \'rate\' not found when adding "
                            "connection")

    try: 
        connection = ModFossa.connection(args['from_state'], args['to_state'], args['rate'])
        markovModel.addConnection(connection)
    except RuntimeError, e:
        print e

def initialState(name):
    try: markovModel.setInitialState(name)
    except RuntimeError, e:
        print e

def maxChannelConductance(conductance):
    try: markovModel.setMaxChannelConductance(conductance)
    except RuntimeError, e:
        print e

def reversalPotential(reversalPotential):
    try: markovModel.setReversalPotential(reversalPotential)
    except RuntimeError, e:
        print e

def membraneCapacitance(capacitance_pf):
    try: markovModel.setMembraneCapacitance(capacitance_pf)
    except RuntimeError, e:
        print e

def isValid():
    return markovModel.isValid()

def validate():
    results = experiment.validate()
    print 'Validation results:',

    if len(results) == 0:
        print 'model is valid.'

    else:
        print 'model is invalid. See details below.'
        for r in results:
            print r

def voltageProtocol(name):
    try: 
        vp = ModFossa.voltageProtocol(name)
        experiment.addVoltageProtocol(vp)
    except RuntimeError, e:
        print e

def voltageProtocolAddStage(vpName, stageName, **args):
    if len(args) == 2:
        _addConstantVoltageStage(vpName, stageName, **args)

    elif len(args) == 4:
        _addSteppedVoltageStage(vpName, stageName, **args)

    else:
        print 'Incorrent number of arguments to voltageProtocolAddStage'

def experimentSweep(name, voltageProtocolName, **args):
    try: 
        exp = ModFossa.experimentSweep(name, voltageProtocolName)

        for k, v in args.items():
            exp.addConcentration(ModFossa.concentration(k, v))

        experiment.addExperimentSweep(exp)

    except RuntimeError, e:
        print e

def run():
    try:
        simulationRunner.runAllExperimentSweeps()

    except RuntimeError, e:
        print e

def getStateProbabilities(experimentSweepName):
    try:
        return results.getStateProbabilities(experimentSweepName)

    except RuntimeError, e:
        print e

def getVoltageProtocol(experimentSweepName):
    try:
        return results.getVoltageProtocol(experimentSweepName)

    except RuntimeError, e:
        print e

def getStateNames():
    try:
        return results.getStateNames()

    except RuntimeError, e:
        print e  

def getCurrents(experimentSweepName):
    try:
        return results.getCurrents(experimentSweepName)

    except RuntimeError, e:
        print e  

def getConductances(experimentSweepName):
    try:
        return results.getConductances(experimentSweepName)

    except RuntimeError, e:
        print e  

def getIV(experimentSweepName, time_ms):
    try:
        return results.getIV(experimentSweepName, time_ms)

    except RuntimeError, e:
        print e 


def _addConstantRateConstant(name, **args):
    if not 'k' in args:
        raise RuntimeError("argument \'k\' not found when adding "
                            "ConstantRateConstant \'' + name + '\'")

    try: rateConstant = ModFossa.constantRateConstant(name, args['k'])
    except RuntimeError, e:
        print e

    try: markovModel.addRateConstant(rateConstant)
    except RuntimeError, e:
        print e

def _addLigandGatedRateConstant(name, **args):
    if not 'k' in args:
        raise RuntimeError("argument \'k\' not found when adding "
                            "LigandGatedRateConstant \'' + name + '\'")

    if not 'ligand' in args:
        raise RuntimeError("argument \'ligand\' not found when adding "
                            "LigandGatedRateConstant \'' + name + '\'")

    if not 'power' in args:
        raise RuntimeError("argument \'power\' not found when adding "
                            "LigandGatedRateConstant \'' + name + '\'")

    try: rateConstant = ModFossa.ligandGatedRateConstant(
        name, args['k'], args['ligand'], args['power'])

    except RuntimeError, e:
        print e

    try: markovModel.addRateConstant(rateConstant)
    except RuntimeError, e:
        print e

def _addSigmoidalRateConstant(name, **args):
    if not 'a' in args:
        raise RuntimeError("argument \'a\' not found when adding "
                            "SigmoidalRateConstant \'' + name + '\'")

    if not 'v_half' in args:
        raise RuntimeError("argument \'v_half\' not found when adding "
                            "SigmoidalRateConstant \'' + name + '\'")

    if not 'k' in args:
        raise RuntimeError("argument \'k\' not found when adding "
                            "SigmoidalRateConstant \'' + name + '\'")

    try: 
        rateConstant = ModFossa.sigmoidalRateConstant(
        name, float(args['a']), float(args['v_half']), float(args['k']))

        markovModel.addRateConstant(rateConstant)
    except RuntimeError, e:
        print e

def _addExponentialRateConstant(name, **args):
    if not 'k' in args:
        raise RuntimeError("argument \'k\' not found when adding "
                            "ExponentialRateConstant \'' + name + '\'")

    if not 'a' in args:
        raise RuntimeError("argument \'a\' not found when adding "
                            "ExponentialRateConstant \'' + name + '\'")

    try: rateConstant = ModFossa.exponentialRateConstant(
        name, args['a'], args['k'])

    except RuntimeError, e:
        print e

    try: markovModel.addRateConstant(rateConstant)
    except RuntimeError, e:
        print e

def _addSteppedVoltageStage(vpName, stageName, **args):

    if not 'start' in args:
        raise RuntimeError("argument \'start\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    if not 'stop' in args:
        raise RuntimeError("argument \'stop\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    if not 'step' in args:
        raise RuntimeError("argument \'step\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    if not 'duration' in args:
        raise RuntimeError("argument \'duration\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    try: 
        vp = experiment.getVoltageProtocol(vpName)
        vp.addSteppedStage(stageName, args['start'], args['stop'], 
            args['step'], args['duration'])
    except RuntimeError, e:
        print e

def _addConstantVoltageStage(vpName, stageName, **args):
    if not 'voltage' in args:
        raise RuntimeError("argument \'voltage\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    if not 'duration' in args:
        raise RuntimeError("argument \'duration\' not found when adding "
                            "VoltageProtocolStage \'' + stageName + '\'")

    try: 
        vp = experiment.getVoltageProtocol(vpName)
        vp.addConstantStage(stageName, args['voltage'], args['duration'])
    except RuntimeError, e:
        print e


#### Plotting ####
def plotStates(experimentSweepName):
    plotData = getStateProbabilities(experimentSweepName)
    names = getStateNames()

    fig = plt.figure(1)
    ax = fig.add_subplot(111)
    ax.plot(plotData[0])

    leg = ax.legend(names, 'center right', shadow=True)
    #ax.set_xlabel('Time (ms)')
    #ax.set_ylabel('Probability')
    #ax.set_title('Channel Probability')
    #ax.autoscale_view(True,True,True)
    #plt.axis([0, 2000, -100, 200])
    plt.show()

def plotVoltageProtocol(experimentSweepName):
    fig = plt.figure(figsize=(10,10), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)
    plotData = getVoltageProtocol(experimentSweepName)
    
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
    fig = plt.figure(figsize=(10,10), facecolor='w', edgecolor='k') 
    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        plotData = getCurrents(name)
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


def plotMultipleIV(sweeps, prefix, time_ms, ymin, ymax, labelheight):
    fig = plt.figure(figsize=(10,10), facecolor='w', edgecolor='k') 
    for i, sweep in enumerate(sweeps):
        name = prefix + str(sweep)

        plotData = getIV(name, time_ms)
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
    fig = plt.figure(figsize=(4,4), facecolor='w', edgecolor='k') 
    ax = fig.add_subplot(111)

    # First, get number of voltages that we have, N.
    # We will create N lists to plot.
    conductances = getConductances(prefix + str(sweeps[0]))
    gAtVoltages=[]

    for i in range(len(conductances)):
        gAtVoltages.append([])
    print len(gAtVoltages)

    for i in range(len(gAtVoltages)):
        gAtVoltages[i].append([])
        gAtVoltages[i].append([])

    for sweep in sweeps:
        name = prefix + str(sweep)

        conductances = getConductances(name)
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
    #ax.set_title(name)
    ax.minorticks_on()
    #ax.set_xticks([-100, -60, -20, 20, 60, 100, 140])
    plt.xlim(xmax = 1100)
    #plt.xlim(xmin=-110)
    #plt.text(-100, labelheight, str(sweep) + 'nM [Ca]i')

    plt.show()
    return fig