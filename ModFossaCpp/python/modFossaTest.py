from modFossa import *

state('open', True)
state('closed')

# connect(from, to, rate)
connect('open', 'closed', 'koff')
connect('closed', 'open', 'kon')

rate('kon', type='constant', k=10)
rate('koff', type='constant', k=1)

#rate('k2', type='ligandGated', k=2.2, ligand='Ca', power=4.0)

initialState('closed')


voltageProtocol('protocol1')
voltageProtocolAddStage('protocol1', 'start', voltage=-50, duration=500)
#voltageProtocolAddStage('protocol1', 'step', start=-60, stop=20, step=20, duration=200)


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
print iterationResults1[0][0]
## Do ALL the plotting ##                                                       
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.plot(iterationResults1)
#ax.plot(mat[:,1])
#ax.plot(mat[:,2])

leg = ax.legend(('C1', 'C2', 'O'), 'center right', shadow=True)
ax.set_xlabel('Time (ms)')
ax.set_ylabel('Probability')
ax.set_title('Channel Probability')

plt.show()
