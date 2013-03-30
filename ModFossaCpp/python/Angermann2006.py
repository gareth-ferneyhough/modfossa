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
maxChannelConductance(1.12)
reversalPotential(0)

voltageProtocol('vp')
#voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=1)
#voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=1)
#voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=1)
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=500)
#voltageProtocolAddStage('vp', 'step', voltage=100, duration=500)
voltageProtocolAddStage('vp', 'step2', start=-80, step=20, stop=40, duration=300)
voltageProtocolAddStage('vp', 'hold2', voltage=-40, duration=300)

experimentSweep('sweep', 'vp', Ca=250e-9)

validate()
run()

#plotStates('sweep')
plotCurrents('sweep')

#voltageProtocol = getVoltageProtocol('sweep')
#plot(voltageProtocol)


