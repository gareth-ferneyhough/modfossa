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
connect(from_state='C1', to_state='C2', rate='kon')
connect(from_state='C2', to_state='C3', rate='kon')
connect(from_state='C3', to_state='C4', rate='kon')

connect(from_state='C4', to_state='C3', rate='koff')
connect(from_state='C3', to_state='C2', rate='koff')
connect(from_state='C2', to_state='C1', rate='koff')

connect(from_state='C2', to_state='O1', rate='a1')
connect(from_state='C3', to_state='O2', rate='a2')
connect(from_state='C4', to_state='O3', rate='a3')

connect(from_state='O1', to_state='C2', rate='b1')
connect(from_state='O2', to_state='C3', rate='b2')
connect(from_state='O3', to_state='C4', rate='b3')

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

plotIV('sweep', 1200)

#plotCurrents('sweep')

#voltageProtocol = getVoltageProtocol('sweep')
#plot(voltageProtocol)


