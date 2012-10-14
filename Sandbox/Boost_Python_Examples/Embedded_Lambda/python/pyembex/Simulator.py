import libpyembex

class LambdaHook(libpyembex.ActionHook):
    def __init__(self, action):
        super(LambdaHook, self).__init__()
        self.action = action
    def runHook(self):
        self.action()
            

class Simulator:
    def __init__(self):
        self.c_sim = libpyembex.Simulator()
    def run_sim(self):
        self.c_sim.runSim()
    def add_hook(self, x):
        self.c_sim.addHook(x)
    def set_number_of_iterations(self, x):
        self.c_sim.setNumberOfIterations(x)
    def add_lambda_hook(self, action):
        self.c_sim.addHook(LambdaHook(action))
        pass



