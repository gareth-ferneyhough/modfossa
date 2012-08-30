import sys
import libpyembex

simulator = libpyembex.Simulator()

if sys.platform == 'win32':
    simulator.setNumberOfIterations(5)
else:
    simulator.setNumberOfIterations(4)

class PythonHook(libpyembex.ActionHook):
    def runHook(self):
        print "I am in python and I am totally running inside your sim"


simulator.addHook(PythonHook())

simulator.runSim()


