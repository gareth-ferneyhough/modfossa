/* 
 * File:   Simulator.h
 * Author: gareth
 *
 * Created on March 24, 2013, 12:26 PM
 */

#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <ModFossa/Common/TransitionMatrix.h>
#include <ModFossa/Common/StateOfTheWorld.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Experiment/ODESolver.h>
#include <ModFossa/Experiment/Results.h>
#include <ModFossa/Experiment/SerializedProtocol.h>

namespace ModFossa {
class Simulator {
public:
    typedef shared_ptr<Simulator>::type SharedPointer;
    
    Simulator();
    ~Simulator();
    
ProtocolIterationResults runProtocolIteration(
        ProtocolIteration protocol_iteration,   
        StateOfTheWorld state_of_the_world, 
        TransitionMatrix transition_matrix);

private:
    ODESolver ode_solver;

};
}

#endif	/* SIMULATOR_H */

