def add_constant_rate_constant(name, **args):
    if not 'k' in args:
        raise RuntimeError('arguement \'k\' not found when adding ConstantRateConstant \'' + name + '\'')
    print 'adding constant rate constant: ' + name




def add_state(name, conducting=False):
    print 'adding State ' + name

def add_rate(name, **args):
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

def add_connection(name, from_state, to_state):
    pass