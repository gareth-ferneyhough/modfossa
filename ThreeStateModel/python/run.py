import numpy
import pyublas
import matplotlib.pyplot as plt
from libModFossa import *

addState('C1')
addState('C2')
addState('O') 
setConducting('O')


kon1 = 1
koff1 = 100
kon2 = 1

addRateConstant('sigmoidal', 70, 60, -40, 'beta1')
addRateConstant('constant', 1, 0, 0, 'kon1')
addRateConstant('constant', 100, 0, 0, 'koff1')
addRateConstant('constant', 1, 0, 0, 'kon2')
addRateConstant('constant', 100, 0, 0, 'koff2')

connect('C1', 'C2', 'kon1')
connect('C2', 'C1', 'koff1')
connect('C2', 'O', 'kon2')
connect('O', 'C2', 'beta1')

setInitialState('O')
setIntegrationWindow(0, 0.001, 0.1);

## Set voltage protocol. Units are in seconds and mV ##
setVstep(-100, 20, 140)
setVholdStart(-50)
setVholdFinish(-80)
setEventTimes(0, 0.1, 1.1, 2.1)

mat = run()
voltageProtocol = getVoltageProtocol()

## Do ALL the plotting ## 
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.plot(mat[:,0])
ax.plot(mat[:,1])
ax.plot(mat[:,2])

leg = ax.legend(('C1', 'C2', 'O'), 'center right', shadow=True)
ax.set_xlabel('Time (ms)')
ax.set_ylabel('Probability')
ax.set_title('Channel Probability')

#plt.show()

## Plot voltage protocol ##
fig = plt.figure(2)
ax = fig.add_subplot(111)
for row in range(voltageProtocol.shape[0]):
    ax.plot(voltageProtocol[row,:])
    
ax.set_xlabel('Time (ms)')
ax.set_ylabel('Voltage (mV)')
ax.set_title('Voltage Protocol')    
    
plt.show()