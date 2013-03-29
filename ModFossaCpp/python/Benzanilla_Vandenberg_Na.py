from modFossa import *


rt_over_f = 24

rate('y', type='exponential', a=16609, k = 1.50 * 0.22 / rt_over_f)
rate('a', type='exponential', a=5750, k = 0.42 * 0.99 / rt_over_f)
rate('c', type='exponential', a=15669, k = 1.91 * 0.75 / rt_over_f)
rate('f', type='exponential', a=432, k = 0.91 * 0.001 / rt_over_f)
rate('g', type='exponential', a=770, k = 0.91 * 0.99 / rt_over_f)
rate('z', type='exponential', a=971, k = -1.50 * 0.78 / rt_over_f)
rate('b', type='exponential', a=4325, k = 0.42 * 0.01 / rt_over_f)
rate('d', type='exponential', a=1361, k = -1.91 * 0.25 / rt_over_f)
rate('i', type='exponential', a=4, k = -0.91 * 0.999 / rt_over_f)
rate('j', type='exponential', a=385.0/54, k = -0.03788) # j = (g*i)/f

state('C1')
state('C2')
state('C3')
state('C4')
state('C5')
state('I4')
state('I5')
state('I')
state('O', conducting=True)

# connect from, to, rate
# todo: make this explicit in the python library
connect('C1', 'C2', 'y')

connect('C2', 'C1', 'z')
connect('C2', 'C3', 'y')

connect('C3', 'C2', 'z')
connect('C3', 'C4', 'y')

connect('C4', 'C3', 'z')
connect('C4', 'I4', 'g')
connect('C4', 'C5', 'a')

connect('C5', 'C4', 'b')
connect('C5', 'O', 'c')

connect('I4', 'C4', 'j')
connect('I4', 'I5', 'a')

connect('I5', 'I4', 'b')
connect('I5', 'I', 'c')

connect('I', 'I5', 'd')
connect('I', 'O', 'i')

connect('O', 'C5', 'd')
connect('O', 'I', 'f')



initialState('C1')


voltageProtocol('protocol1')
voltageProtocolAddStage('protocol1', 'start', voltage=-108, duration=500)
voltageProtocolAddStage('protocol1', 'start', voltage=-40, duration=500)
#voltageProtocolAddStage('protocol1', 'step', start=-60, stop=20, step=20, duration=200)


experimentSweep('sweep1', 'protocol1')
results = validate()
print 'validation results:'
for r in results:
	print r


simulationRunner.runExperimentSweep('sweep1')
sweepResults = simulationRunner.getExperimentSweepResults('sweep1')

print 'number of protocol iterations: ', len(sweepResults)
print 'number of time steps', len(sweepResults[0])
print 'number of states', len(sweepResults[0][0])

iterationResults1 = sweepResults[0]

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

