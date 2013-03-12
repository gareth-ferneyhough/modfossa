/* 
 * File:   TransitionMatrix.h
 * Author: gareth
 *
 * Created on March 11, 2013, 5:01 PM
 */

#ifndef TRANSITIONMATRIX_H
#define	TRANSITIONMATRIX_H

#include <ModelDefinition/Matrix.h>
#include <ModelDefinition/MarkovModel.h>

namespace ModelDefinition {

    class TransitionMatrix {
    public:
        TransitionMatrix();
        TransitionMatrix(const TransitionMatrix& orig);
        virtual ~TransitionMatrix();
        void create(const MarkovModel& markov_model);
        mat get() const;
        void update();

    private:
        mat transition_matrix;
    };
}

#endif	/* TRANSITIONMATRIX_H */

