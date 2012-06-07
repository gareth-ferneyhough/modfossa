import numpy
import pyublas
import matplotlib.pyplot as plt
import libModFossa


mat = libModFossa.solve()

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(mat[:,0])
ax.plot(mat[:,1])
ax.plot(mat[:,2])

leg = ax.legend(('C1', 'C2', 'O'), 'center right', shadow=True)
ax.set_xlabel('Time (ms)')
ax.set_ylabel('Probability')
ax.set_title('Channel Probability')

plt.show()

