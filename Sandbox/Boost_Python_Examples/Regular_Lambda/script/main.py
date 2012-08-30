import pyembex
import sys

s = pyembex.Simulator()
s.set_number_of_iterations(5)
s.set_lambda_hook(lambda x : x * 2)
s.run_sim()

