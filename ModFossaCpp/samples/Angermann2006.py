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

initialState('C1') # todo: this should not be required, since we are getting to steady state
membraneCapacitance(100) # todo: this should not be required either

maxChannelConductance(1.16)
reversalPotential(0)

voltageProtocol('vp')
voltageProtocolAddStage('vp', 'hold', voltage=-50, duration=100)
voltageProtocolAddStage('vp', 'step', start=-100, stop=140, step=20, duration=1000)
voltageProtocolAddStage('vp', 'hold2', voltage=-80, duration=500)

sweeps = []
sweeps.append(20)
sweeps.append(100)
sweeps.append(250)
sweeps.append(500)
sweeps.append(750)
sweeps.append(1000)

for sweep in sweeps:
	name = 'angermann_ca' + str(sweep)
	concentration = sweep*pow(10, -9)
	experimentSweep(name, 'vp', Ca=concentration)

validate()
run()


iv_late = plotMultipleIV(sweeps, 'angermann_ca', 1099, -10, 50, 40)
iv_late.savefig('../results/' + 'angermann_ca_late.eps', format='eps')

iv_tail = plotMultipleIV(sweeps, 'angermann_ca', 1100, -30, 30, 20)
iv_tail.savefig('../results/' + 'angermann_ca_tail.eps', format='eps')

currents = plotMultipleCurrents(sweeps, 'angermann_ca')
currents.savefig('../results/' + 'angermann_ca_currents.eps', format='eps')

gVsCa = plotGvsCa(sweeps, 'angermann_ca', 1099)
gVsCa.savefig('../results/' + 'angermann_ca_g_vs_cai.eps', format='eps')

gVsV = plotGvsV(sweeps, 'angermann_ca', 1099)
gVsV.savefig('../results/' + 'angermann_ca_g_vs_v.eps', format='eps')

voltageProtocol = plotVoltageProtocol('angermann_ca' + str(sweeps[0]))
voltageProtocol.savefig('../results/' + 'angermann_ca_voltage_protocol.eps', format='eps')


