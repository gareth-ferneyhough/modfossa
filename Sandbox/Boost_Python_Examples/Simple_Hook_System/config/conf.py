import sys

print "Starting configuration process"

if sys.platform == 'win32':
    simulator.setNumberOfIterations(5)
else:
    simulator.setNumberOfIterations(12)

class PythonHook(ActionHook):
    def runHook(self):
        print "I am in python and I am totally running inside your sim"


simulator.addHook(PythonHook())

x = 7

