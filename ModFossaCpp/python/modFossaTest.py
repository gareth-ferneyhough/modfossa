from modFossa import *

state('state1')
state('state1', False)
state('state2', False)

connect('state1', 'state2', 'k1')
connect('state1', 'state2', 'k2')

rate('k1', type='constant', k=1.2)
rate('k1', type='constant', k=1.2)

rate('k2', type='ligandGated', k=2.2, ligand='Ca', power=4.0)

initialState('state1')


voltageProtocol('protocol1')
voltageProtocolAddStage('protocol1', 'start', voltage=-50, duration=200)
voltageProtocolAddStage('protocol1', 'step', start=-60, stop=20, step=20, duration=200)


experimentSweep('ca1', 'protocol1', Ca=2, Na=3)


results = validate()
print 'validation results:'
for r in results:
	print r


simulationRunner.runExperimentSweep('ca1')