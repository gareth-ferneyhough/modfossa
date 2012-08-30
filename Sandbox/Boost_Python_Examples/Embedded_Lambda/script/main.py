import pyembex
import sys
s = pyembex.Simulator()
s.set_number_of_iterations(5)
s.add_lambda_hook(lambda : sys.stdout.write("I am a lambda\n"))
s.run_sim()

