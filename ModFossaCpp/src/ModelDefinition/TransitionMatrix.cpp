/* 
 * File:   TransitionMatrix.cpp
 * Author: gareth
 * 
 * Created on March 11, 2013, 5:01 PM
 */

#include <ModelDefinition/TransitionMatrix.h>

namespace ModelDefinition {

    TransitionMatrix::TransitionMatrix() {
    }

    TransitionMatrix::TransitionMatrix(const TransitionMatrix& orig) {
    }

    TransitionMatrix::~TransitionMatrix() {
    }

    void TransitionMatrix::create(const MarkovModel& markov_model) {
        //transition_matrix << 1 << 2 << 3 << endr;
        

        

    }
    
    
    
    mat TransitionMatrix::get() const {
        return transition_matrix;
    }
}