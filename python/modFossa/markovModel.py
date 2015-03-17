from globals import *

def state(name, conducting = False, gating = 1.0):
    """Add a new state to the markov model.

    :param name: name of the state. Must be unique.
    :param conducting: whether or not the state is a conducting state.
                       False by default.
    :param gating: scales the conductance of the state. Only used 
                   *conducting* is True. Default value is 1.0. 
    """
    try: state = ModFossa.state(name, conducting, gating)
    except RuntimeError, e:
        print e

    try:
        markovModel.addState(state)
    except RuntimeError, e:
        print e

def rate(name, **args):
    u"""Create a rate constant.

    :param name: name of the rate constant. Must be unique.
    :param args: required arguments specifying the type and parameters of the rate constant.

    The type of rate constant to create is specified by the
    *type* argument. This is required. The various rate constant
    types and their required arguments are listed below.

    **constant**

    A rate constant with with a single rate, not dependent on 
    voltage or ligand concentration.

    Required arguments\:
      * k 

    Implementation\: :math:`rate = k`.

    Example::
      
      rate('myConstantRate', type='constant', k=10)

    **boltzman**
   
    A voltage dependent rate constant using the 
    Boltzman equation.

    Required arguments\:
      * a
      * v_half
      * k 

    Implementation\: :math:`rate(V) = \\frac{a}{1+exp[(V-V\_{0.5}) / k]}`.

    Example::
      
      rate('myBoltzmanRate', type='boltzman', a=1, v_half=-30, k=10)

    **exponential**

    An exponential voltage dependent rate constant 

    Required arguments\:
      * a
      * k 

    Implementation\: :math:`rate(V) = a * exp(k * V)`.

    Example::
      
      rate('myExponentialRate', type='exponential', a=1, k=10)

    **ligandGated**

    A ligand gated rate constant 

    Required arguments\:
      * ligand
      * ligand_power
      * k 

    Implementation\: :math:`rate([ligand]) = k * [ligand]^{ligand\_power}` 
    where :math:`[ligand]` is the concentration of *ligand*.

    Example::
      
      rate('myLigandGatedRate', type='ligandGated', ligand='Ca', ligand_power=3, k=50)
    """
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

def connect(fromState, toState, rate):
    """Connect two states with the given rate constant."""
    try: 
        connection = ModFossa.connection(fromState, toState, rate)
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

    try: _markovModel.addRateConstant(rateConstant)
    except RuntimeError, e:
        print e



