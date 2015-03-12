from globals import _experiment, _modFossaCpp, _simulationRunner
from collections import defaultdict


_startAtSteadyState = True;
_concentrationProtocols = defaultdict(list)
_experimentSweepNames   = defaultdict(list)


def voltageProtocol(name):
    try: 
        vp = _modFossaCpp.voltageProtocol(name)
        _experiment.addVoltageProtocol(vp)
    except RuntimeError, e:
        print e

def voltageProtocolAddStage(vpName, stageName, **args):
    if len(args) == 2:
        _addConstantVoltageStage(vpName, stageName, **args)

    elif len(args) == 4:
        _addSteppedVoltageStage(vpName, stageName, **args)

    else:
        print 'Incorrect number of arguments to voltageProtocolAddStage'


def concentrationProtocol(name):
    r"""Declare a new concentration protocol with the given name.

       Concentration values must be added using :meth:`addConcentration`
    """
    _concentrationProtocols[name]

def addConcentration(cpName, **args):
    """Add a concentration value to the concentration protocol *cpName*.

       :param cpName: name of concentration protocol to append the value to. It must be declared first using :meth:`concentrationProtocol`.
       :param args: required arguments specifying the ligand its concentration. See example below for more information.

       The following example adds a calcium concentration of 200 nM to *myConcentrations* ::
      
         addConcentration('myConcentrations', Ca=200E-9)
     """

    if not cpName in _concentrationProtocols:
        print 'concentration protocol', cpName, 'not defined'

    else:
        for ligand, concentration in args.items():
            _concentrationProtocols[cpName].append((ligand, concentration))


def experiment(name, voltageProtocolName, concentrationProtocolName):
    """Create an experiment using the given voltage and concentration
       protocols. 

       For each concentration in the concentration protocol, the 
       voltage protocol will be run through. This is equivalent to using the 
       method :meth:`experimentSweep` to add each concentration value
       manually. 

       Individual experiment sweep results can be obtained and plotted using
       the generated *name_ligand_concentration*. 

       For example,::

         concentrationProtocol('concentrations')
         concentrationProtocolAddStage('concentrations', Ca=20E-9)
         concentrationProtocolAddStage('concentrations', Ca=100E-9)
         experiment('myExperiment', 'myVoltageProtocol', 'concentrations')
         validate()
         run()

       will run *myVoltageProtocol* using a Ca concentration of 20 nM, 
       followed by a Ca concentration of 100 nM. The two experiment sweeps
       will be named *myExperiment_Ca_20E-9*, and *myExperiment_Ca_100E-9*.
       These two names can be used to plot the experiment sweeps using the 
       *single* plotting methods, such as :meth:`plotSingleIV` and 
       :meth:`plotSingleCurrents`. 

       The *multiple* plotting methods will plot all the experiment sweeps
       from the given experiment on a single plot. For example, the following
       snippet will plot the two individual IV curves from the experiment 
       defined above on a single plot\:::

         plotMultipleIV(myExperiment, time=1100)
    """

    for i in _concentrationProtocols[concentrationProtocolName]:
        experimentSweepName = name + '_' + i[0] + '_' + str(i[1])

        try: 
            exp = _modFossaCpp.experimentSweep(experimentSweepName, voltageProtocolName)
            exp.addConcentration(_modFossaCpp.concentration(i[0], i[1]))
            _experiment.addExperimentSweep(exp)
            _experimentSweepNames[name].append(experimentSweepName)

        except RuntimeError, e:
            print e

def experimentSweep(name, voltageProtocolName, **args):
    try: 
        exp = _modFossaCpp.experimentSweep(name, voltageProtocolName)

        for k, v in args.items():
            exp.addConcentration(_modFossaCpp.concentration(k, v))

        _experiment.addExperimentSweep(exp)

    except RuntimeError, e:
        print e

def run():
    try:
        _simulationRunner.runAllExperimentSweeps(_startAtSteadyState)

    except RuntimeError, e:
        print e

def startAtSteadyState(value):
    global _startAtSteadyState
    _startAtSteadyState = value

def isValid():
    return markovModel.isValid()

def validate():
    results = _experiment.validate()
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
        vp = _experiment.getVoltageProtocol(vpName)
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
        vp = _experiment.getVoltageProtocol(vpName)
        vp.addConstantStage(stageName, args['voltage'], args['duration'])
    except RuntimeError, e:
        print e

