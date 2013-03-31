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

state('O1', conducting=True, gating=1.0)
state('O2', conducting=True, gating=0.5)
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

rate('koff', type='constant', k=50)
rate('kon', type='ligandGated', k=25e6, ligand='Ca', power=1)

rate('a1', type='constant', k=1)
rate('a2', type='constant', k=25)
rate('a3', type='constant', k=200)

rate('b1', type='sigmoidal', a=60, v_half=-40, k=40)
rate('b2', type='sigmoidal', a=35, v_half=0, k=50)
rate('b3', type='sigmoidal', a=25, v_half=140, k=40)

initialState('C1')
maxChannelConductance(1.16)
reversalPotential(0)

voltageProtocol('vp')
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=100)
voltageProtocolAddStage('vp', 'step', start=-100, stop=140, step=20, duration=1000)
voltageProtocolAddStage('vp', 'hold2', voltage=-80, duration=1000)


experimentSweep('sweep', 'vp', Ca=1000e-9)

validate()
run()


currents = getCurrents('sweep')
plotCurrents('sweep')

#voltageProtocol = getVoltageProtocol('sweep')
#plot(voltageProtocol)


