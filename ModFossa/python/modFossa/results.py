from globals import results

def getStateProbabilities(experimentSweepName):
    try:
        return results.getStateProbabilities(experimentSweepName)

    except RuntimeError, e:
        print e

def getVoltageProtocol(experimentSweepName):
    try:
        return results.getVoltageProtocol(experimentSweepName)

    except RuntimeError, e:
        print e

def getStateNames():
    try:
        return results.getStateNames()

    except RuntimeError, e:
        print e  

def getCurrents(experimentSweepName):
    try:
        return results.getCurrents(experimentSweepName)

    except RuntimeError, e:
        print e  

def getConductances(experimentSweepName):
    try:
        return results.getConductances(experimentSweepName)

    except RuntimeError, e:
        print e  

def getIV(experimentSweepName, time_ms):
    try:
        return results.getIV(experimentSweepName, time_ms)

    except RuntimeError, e:
        print e 
