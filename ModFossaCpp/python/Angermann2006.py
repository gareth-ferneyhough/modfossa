#
#   This model is based on the paper: "Mechanism of the Inhibition
#   of Ca2+-Activated Cl- Currents by Phosphorylation in Pulmonary
#   Arterial Smooth Muscle Cells" Angermanm et al. J. Gen Physiol.
#   July 2006.
#
#         kon [Ca] ->    kon [Ca] ->    kon [Ca] ->    
#      C1             C2             C3             C4
#          <-  koff       <-  koff       <-  koff    
#                      ^              ^              ^
#                  a1 || b1       a2 || b2       a3 || b3
#                     v              v              v
#                     O1             O2             O3

from modFossa import *

state('O1', conducting=True)
state('O2')
state('O3')
state('C1')
state('C2')
state('C3')
state('C4')

# connect(from, to, rate)
connect('C1', 'C2', 'kon')
connect('C2', 'C3', 'kon')
connect('C3', 'C4', 'kon')

connect('C4', 'C3', 'koff')
connect('C3', 'C2', 'koff')
connect('C2', 'C1', 'koff')

connect('C2', 'O1', 'a1')
connect('C3', 'O2', 'a2')
connect('C4', 'O3', 'a3')

connect('O1', 'C2', 'b1')
connect('O2', 'C3', 'b2')
connect('O3', 'C4', 'b3')

#maxConductance(1.16)
#reversalPotential(0)

rate('koff', type='constant', k=50)
rate('kon', type='ligandGated', k=20e6, ligand='Ca', power=1)

rate('a1', type='constant', k=75)
rate('a2', type='constant', k=150)
rate('a3', type='constant', k=300)

rate('b1', type='sigmoidal', a=10, v_half=75, k=50)
rate('b2', type='sigmoidal', a=75, v_half=120, k=50)
rate('b3', type='sigmoidal', a=100, v_half=120, k=50)

initialState('C1')

voltageProtocol('vp')
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=500)
voltageProtocolAddStage('vp', 'step', voltage=100, duration=500)

experimentSweep('sweep', 'vp', Ca=250e-9)



results = validate()
print 'validation results:'
for r in results:
	print r



## Put this code in the library
simulationRunner.runExperimentSweep('sweep')
sweepResults = simulationRunner.getExperimentSweepResults('sweep')

print 'number of protocol iterations: ', len(sweepResults)
print 'number of time steps', len(sweepResults[0])
print 'number of states', len(sweepResults[0][0])

iterationResults1 = sweepResults[0]


### calculate current ###
for i in iterationResults1:
	probs = ''
	for j in i:
		probs += str(j)
	print probs



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