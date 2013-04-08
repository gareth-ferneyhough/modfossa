from modFossa import *

state('Open')
state('Closed')

connect(from_state='Closed', to_state='Open', rate='kon')
connect(from_state='Open', to_state='Closed', rate='koff')

rate('kon', type='constant', k=10)
rate('koff', type='constant', k=1)

initialState('Closed')
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
experimentSweep('two_state', 'vp')

validate()
run()

states = plotStates('two_state')
states.savefig('../results/' + 'two_state_probabilities.eps', format='eps')


