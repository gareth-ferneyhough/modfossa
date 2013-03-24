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
#include <ModFossa/ModelDefinition/MarkovModel.h>

namespace ModFossa {

class TransitionMatrix {
public:
    TransitionMatrix(const MarkovModel& markov_model);
    ~TransitionMatrix();
    Matrix get() const;
    void update(StateOfTheWorld::SharedPointer state_of_the_world);

private:
    void create(const MarkovModel& markov_model);
    double calculateTotalRate(
            const std::vector<Transition::SharedPointer>& transitions,
            const StateOfTheWorld::SharedPointer state_of_the_world) const;

    Matrix transition_matrix;
    std::vector<std::vector<std::vector<Transition::SharedPointer > > > 
        transitions_3d;
};
}

#endif	/* TRANSITIONMATRIX_H */

