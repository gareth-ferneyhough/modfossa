from modFossa import *

state('state1')
state('state2', False)
#state('state3', False)

connect('state1', 'state2', 'k1')
connect('state2', 'state1', 'k1')
#connect('state2', 'state3', 'k2')
#connect('state3', 'state2', 'k2')

rate('k1', type='constant', k=1.2)
rate('k1', type='constant', k=1.2)

rate('k2', type='ligandGated', k=2.2, ligand='Ca', power=4.0)

initialState('state1')


voltageProtocol('protocol1')
voltageProtocolAddStage('protocol1', 'start', voltage=-50, duration=200)
voltageProtocolAddStage('protocol1', 'step', start=-60, stop=20, step=20, duration=200)


experimentSweep('ca1', 'protocol1', Ca=2.2, Na=3.3)


results = validate()
print 'validation results:'
for r in results:
	print r


simulationRunner.runExperimentSweep('ca1')
sweepResults = simulationRunner.getExperimentSweepResults('ca1')

print 'number of protocol iterations: ', len(sweepResults)
print 'number of time steps', len(sweepResults[0])
print 'number of states', len(sweepResults[0][0])

iterationResults1 = sweepResults[0]

print len(iterationResults1)
for timeStep in iterationResults1:
	probabilities = ''
	for stateProb in timeStep:
		probabilities += ' ' + str(stateProb)
	#print probabilities