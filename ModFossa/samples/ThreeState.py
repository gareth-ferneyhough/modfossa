from modFossa import *

state('C')
state('O1', gating=0.5)
state('O2', conducting=True)

connect(fromState='C', toState='O1', rate='k1')
connect(fromState='O1', toState='O2', rate='k2')
connect(fromState='O1', toState='C', rate='k3')
connect(fromState='O2', toState='O1', rate='k4')

rate('k1', type='ligandGated', k=10e8, ligand='Ca', power=1)
rate('k2', type='constant', k=1)
rate('k3', type='sigmoidal', k=1, a=100, v_half=50)
rate('k4', type='constant', k=4)

initialState('O2')
startAtSteadyState(False)

# These are still required by ModFossa, even though they
# have no effect on our simple model.
maxChannelConductance(1.16)
reversalPotential(0)
membraneCapacitance(100)

# We also need a voltage protocol, although this also has no 
# effect on our simple model apart from the simulation time.
voltageProtocol('vp')
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=500)
voltageProtocolAddStage('vp', 'hold', voltage= 100, duration=500)
experimentSweep('three_state', 'vp', Ca=500e-9)

validate()
run()

states = plotStates('three_state')
#states.savefig('../results/' + 'three_state_probabilities.eps', format='eps')

currents = plotCurrents('three_state')
