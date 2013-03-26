import ModFossa
import matplotlib.pyplot as plt
#class modFossa:
    
  #  def __init__():
simulationRunner = ModFossa.simulationRunner()
experiment = simulationRunner.experiment()
markovModel = experiment.markovModel()

def state(name, conducting = False):
    try: state = ModFossa.state(name, conducting)
    except RuntimeError, e:
        print e

    try:
        markovModel.addState(state)
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

def rate(name, **args):
    if args['type'] == 'constant':
        _addConstantRateConstant(name, **args)
    elif args['type'] == 'sigmoidal':
        print 'sigmoidal'
    elif args['type'] == 'ligandGated':
        _addLigandGatedRateConstant(name, **args)
    elif args['type'] == 'boltzman':
        print 'boltzman'
    elif args['type'] == 'exponential':
        print 'exponential'

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

def isValid():
    return markovModel.isValid()

def validate():
    return experiment.validate()

def voltageProtocol(name):
    try: 
        vp = ModFossa.voltageProtocol(name)
        experiment.addVoltageProtocol(vp)
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