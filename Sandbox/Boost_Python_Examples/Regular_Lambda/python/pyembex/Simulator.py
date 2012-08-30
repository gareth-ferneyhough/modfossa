import libpyembex

class Simulator:
    def __init__(self):
        self.c_sim = libpyembex.Simulator()
        # Boring default
        self.action = lambda : 0.0
    def run_sim(self):
        for x in range(self.number_of_iterations):
            self.c_sim.runSimIteration(x, self.action(x))
    def set_number_of_iterations(self, x):
        self.number_of_iterations = x
    def set_lambda_hook(self, action):
        self.action = action

