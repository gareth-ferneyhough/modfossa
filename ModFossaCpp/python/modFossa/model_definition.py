import ModFossa

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

def validate2():
    return experiment.validate2()