from globals import _results

def getStateProbabilities(experimentSweepName):
    try:
        return _results.getStateProbabilities(experimentSweepName)

    except RuntimeError, e:
        print e

def getVoltageProtocol(experimentSweepName):
    try:
        return _results.getVoltageProtocol(experimentSweepName)

    except RuntimeError, e:
        print e

def getStateNames():
    try:
        return _results.getStateNames()

    except RuntimeError, e:
        print e  

def getCurrents(experimentSweepName):
    try:
        return _results.getCurrents(experimentSweepName)

    except RuntimeError, e:
        print e  

def getConductances(experimentSweepName):
    try:
        return _results.getConductances(experimentSweepName)

    except RuntimeError, e:
        print e  

def getIV(experimentSweepName, time_ms):
    try:
        return _results.getIV(experimentSweepName, time_ms)

    except RuntimeError, e:
        print e 
