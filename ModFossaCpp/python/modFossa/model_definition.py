import ModFossa
import matplotlib.pyplot as plt
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

def connect(name, fromState, toState):
    try: connection = ModFossa.connection(name, fromState, toState)
    except RuntimeError, e:
        print e

    try:
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


def plotCurrents(experimentSweepName):
    plotData = getCurrents(experimentSweepName)
    names = getStateNames()

    fig = plt.figure(1)
    ax = fig.add_subplot(111)
    for currentTrace in plotData:
        ax.plot(currentTrace)

    #leg = ax.legend(names, 'center right', shadow=True)
    #ax.set_xlabel('Time (ms)')
    #ax.set_ylabel('Probability')
    #ax.set_title('Channel Probability')
    #ax.autoscale_view(True,True,True)
    #plt.axis([0, 2000, -100, 200])
    plt.show()

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