from globals import *

_startAtSteadyState = True;

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

