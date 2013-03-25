from modFossa import *


state('state1')
state('state1', False)
state('state2', False)

connect('state1', 'state2', 'k1')
connect('state1', 'state2', 'k2')

rate('k1', type='constant', k=1.2)
rate('k1', type='constant', k=1.2)

rate('k2', type='ligandGated', k=2.2, ligand='Ca', power=4.0)