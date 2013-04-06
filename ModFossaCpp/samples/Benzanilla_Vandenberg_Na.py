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


connect(from_state='C1', to_state='C2', rate='y')

connect(from_state='C2', to_state='C1', rate='z')
connect(from_state='C2', to_state='C3', rate='y')

connect(from_state='C3', to_state='C2', rate='z')
connect(from_state='C3', to_state='C4', rate='y')

connect(from_state='C4', to_state='C3', rate='z')
connect(from_state='C4', to_state='I4', rate='g')
connect(from_state='C4', to_state='C5', rate='a')

connect(from_state='C5', to_state='C4', rate='b')
connect(from_state='C5', to_state='O', rate='c')

connect(from_state='I4', to_state='C4', rate='j')
connect(from_state='I4', to_state='I5', rate='a')

connect(from_state='I5', to_state='I4', rate='b')
connect(from_state='I5', to_state='I', rate='c')

connect(from_state='I', to_state='I5', rate='d')
connect(from_state='I', to_state='O', rate='i')

connect(from_state='O', to_state='C5', rate='d')
connect(from_state='O', to_state='I', rate='f')



initialState('C1')
maxChannelConductance(1.16)
reversalPotential(0)
membraneCapacitance(100)

voltageProtocol('protocol1')
voltageProtocolAddStage('protocol1', 'start', voltage=-108, duration=500)
voltageProtocolAddStage('protocol1', 'start', voltage=10, duration=500)
#voltageProtocolAddStage('protocol1', 'step', start=-60, stop=20, step=20, duration=200)


experimentSweep('sweep1', 'protocol1')
validate()
run()

#plotCurrents('sweep1')
plotStates('sweep1')
