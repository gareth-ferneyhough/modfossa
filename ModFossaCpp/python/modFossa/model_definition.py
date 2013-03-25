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


def add_constant_rate_constant(name, **args):
    if not 'k' in args:
        raise RuntimeError('arguement \'k\' not found when adding ConstantRateConstant \'' + name + '\'')
    print 'adding constant rate constant: ' + name

def rate(name, **args):
    if args['type'] == 'constant':
        add_constant_rate_constant(name, **args)
    elif args['type'] == 'sigmoidal':
        print 'sigmoidal'
    elif args['type'] == 'ligand-gated':
        print 'ligand-gated'
    elif args['type'] == 'boltzman':
        print 'boltzman'
    elif args['type'] == 'exponential':
        print 'exponential'

def connection(name, from_state, to_state):
    pass
