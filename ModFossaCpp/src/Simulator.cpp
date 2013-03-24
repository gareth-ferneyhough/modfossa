/* 
 * File:   Simulator.cpp
 * Author: gareth
 * 
 * Created on March 24, 2013, 12:26 PM
 */

#include <ModFossa/Experiment/Simulator.h>


namespace ModFossa {
Simulator::Simulator() {
}

Simulator::~Simulator() {
}

ProtocolIterationResults Simulator::runProtocolIteration(
        ProtocolIteration protocol_iteration,   
        StateOfTheWorld state_of_the_world, 
        TransitionMatrix transition_matrix) {
    
    // set state_of_the_world initial voltage
    // update transition_matrix
    
    // create ODESolver
    // initialize solver and setup initial conditions
    
    // for each time in protocol_iteration:
        // state_of_the_world.setVoltage(protocol_iteration[i]
        // transition_matrix.update(state_of_the_world)
        // results.append(ode_solver.solve(transition_matrix.get, duration)

    // return results
}
}