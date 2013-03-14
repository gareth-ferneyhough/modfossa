/* 
 * File:   TransitionMatrix.h
 * Author: gareth
 *
 * Created on March 11, 2013, 5:01 PM
 */

#ifndef TRANSITIONMATRIX_H
#define	TRANSITIONMATRIX_H

#include <vector>

#include <ModelDefinition/Transition.h>
#include <ModelDefinition/Matrix.h>
#include <ModelDefinition/MarkovModel.h>

using std::vector;

namespace ModelDefinition {

    class TransitionMatrix {
    public:
        TransitionMatrix(const MarkovModel& markov_model);
        virtual ~TransitionMatrix();
        Matrix get() const;
        void update(StateOfTheWorld::SharedPointer state_of_the_world);

    private:
        void create(const MarkovModel& markov_model);
        double calculateTotalRate(
                const vector<Transition::SharedPointer>& transitions,
                const StateOfTheWorld::SharedPointer state_of_the_world) const;

        Matrix transition_matrix;
        vector<vector<vector<Transition::SharedPointer > > > transitions_3d;
    };
}

#endif	/* TRANSITIONMATRIX_H */

