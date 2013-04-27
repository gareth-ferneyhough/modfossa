from globals import *
import numpy as np

#class modFossa:
    
  #  def __init__():

_startAtSteadyState = True;


def state(name, conducting = False, gating = 1.0):
    try: state = modFossaCpp.state(name, conducting, gating)
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

def startAtSteadyState(value):
    global _startAtSteadyState
    _startAtSteadyState = value

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
        simulationRunner.runAllExperimentSweeps(_startAtSteadyState)

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


