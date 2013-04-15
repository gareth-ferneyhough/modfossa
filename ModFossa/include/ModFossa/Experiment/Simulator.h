/* 
 * File:   Simulator.h
 * Author: gareth
 *
 * Created on March 24, 2013, 12:26 PM
 */

#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <ModFossa/Common/ContainerTypes.h>
#include <ModFossa/Common/TransitionMatrix.h>
#include <ModFossa/Common/StateOfTheWorld.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Experiment/ODESolver.h>
#include <ModFossa/Experiment/SerializedProtocol.h>

namespace ModFossa {
class Simulator {
public:
    typedef shared_ptr<Simulator>::type SharedPointer;
    
    Simulator();
    ~Simulator();
    
    Vector2d runProtocolIteration(
    ProtocolIteration protocol_iteration,   
    StateOfTheWorld::SharedPointer state_of_the_world, 
    TransitionMatrix::SharedPointer transition_matrix,
    bool start_at_steady_state);

private:
    
    // const double dt = 0.001; 
    // Not using currently. Our time step is 
    // one millisecond, and our time units we pass to the solver
    // are in milliseconds.
    
    void resultsMatrixToVector(
        Vector2d& results, const Matrix& mat); 
};
}

#endif	/* SIMULATOR_H */

