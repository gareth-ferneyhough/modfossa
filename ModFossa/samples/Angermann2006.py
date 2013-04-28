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
connect(fromState='C1', toState='C2', rate='kon')
connect(fromState='C2', toState='C3', rate='kon')
connect(fromState='C3', toState='C4', rate='kon')

connect(fromState='C4', toState='C3', rate='koff')
connect(fromState='C3', toState='C2', rate='koff')
connect(fromState='C2', toState='C1', rate='koff')

connect(fromState='C2', toState='O1', rate='a1')
connect(fromState='C3', toState='O2', rate='a2')
connect(fromState='C4', toState='O3', rate='a3')

connect(fromState='O1', toState='C2', rate='b1')
connect(fromState='O2', toState='C3', rate='b2')
connect(fromState='O3', toState='C4', rate='b3')

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

concentrationProtocol('concentrations')
addConcentration('concentrations', Ca=20E-9)
addConcentration('concentrations', Ca=100E-9)
addConcentration('concentrations', Ca=250E-9)
addConcentration('concentrations', Ca=500E-9)
addConcentration('concentrations', Ca=750E-9)
addConcentration('concentrations', Ca=1000E-9)

experiment('angermann', 'vp', 'concentrations')
validate()
run()

# Plotting
currents = plotMultipleCurrents('angermann')
gVsV = plotGvsV('angermann', time_ms = 1099)
gVsCa = plotGvsConcentration('angermann', time_ms = 1099)

iv_late = plotMultipleIV('angermann', 
			 time_ms = 1099, ymin = -10, 
			 ymax = 50, labelHeight = 40)

iv_tail = plotMultipleIV('angermann', 
			 time_ms = 1100, ymin = -30, 
			 ymax = 30, labelHeight = 20)

#iv_late.savefig('../results/' + 'angermann_ca_late.eps', format='eps')
#iv_tail.savefig('../results/' + 'angermann_ca_tail.eps', format='eps')
#currents.savefig('../results/' + 'angermann_ca_currents.eps', format='eps')
#gVsCa.savefig('../results/' + 'angermann_ca_g_vs_cai.eps', format='eps')
#gVsV.savefig('../results/' + 'angermann_ca_g_vs_v.eps', format='eps')
