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
    StateOfTheWorld::SharedPointer state_of_the_world, 
    TransitionMatrix::SharedPointer transition_matrix);

private:
    const double dt = 0.001;
    
    void resultsMatrixToVector(
        ProtocolIterationResults& results, const Matrix& mat); 
};
}

#endif	/* SIMULATOR_H */

