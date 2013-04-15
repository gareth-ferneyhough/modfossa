/* 
 * File:   TransitionMatrix.h
 * Author: gareth
 *
 * Created on March 11, 2013, 5:01 PM
 */

#ifndef TRANSITIONMATRIX_H
#define	TRANSITIONMATRIX_H

#include <vector>

#include <ModFossa/ModelDefinition/Transition.h>
#include <ModFossa/Common/Matrix.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/ModelDefinition/MarkovModel.h>

namespace ModFossa {

class TransitionMatrix {
public:
    typedef shared_ptr<TransitionMatrix>::type SharedPointer;
    
    TransitionMatrix(const MarkovModel& markov_model);
    ~TransitionMatrix();
    Matrix get() const;
    void update(StateOfTheWorld::SharedPointer state_of_the_world);
    int getInitialStateIndex() const;

private:
    void create(const MarkovModel& markov_model);
    double calculateTotalRate(
            const std::vector<Transition::SharedPointer>& transitions,
            const StateOfTheWorld::SharedPointer state_of_the_world) const;

    int initial_state_index;
    Matrix transition_matrix;
    std::vector<std::vector<std::vector<Transition::SharedPointer > > > 
        transitions_3d;
};
}

#endif	/* TRANSITIONMATRIX_H */

