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
state('O2')
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

rate('a1', type='constant', k=5)
rate('a2', type='constant', k=20)
rate('a3', type='constant', k=50)

rate('b1', type='sigmoidal', a=250, v_half=-40, k=50)
rate('b2', type='sigmoidal', a=75, v_half=-20, k=40)
rate('b3', type='sigmoidal', a=50, v_half=40, k=30)

initialState('C1') # todo: this should not be required, since we are getting to steady state
maxChannelConductance(1.16)
reversalPotential(0)
membraneCapacitance(100)

voltageProtocol('vp')
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=100)
voltageProtocolAddStage('vp', 'step', start=-100, stop=140, step=20, duration=1000)
voltageProtocolAddStage('vp', 'hold2', voltage=-80, duration=500)


experimentSweep('a9c_control', 'vp', Ca=500e-9)

validate()
run()

plotIV('a9c_control', 1100)
plotCurrents('a9c_control')
#voltageProtocol = getVoltageProtocol('sweep')
#plot(voltageProtocol)


