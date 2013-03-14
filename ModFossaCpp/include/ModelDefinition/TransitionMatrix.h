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
        TransitionMatrix();
        TransitionMatrix(const TransitionMatrix& orig);
        virtual ~TransitionMatrix();
        void create(const MarkovModel& markov_model);
        mat get() const;
        void update();

    private:
        Mat<double> transition_matrix;
        vector<vector<vector<Transition::SharedPointer > > >transitions; 
    };
}

#endif	/* TRANSITIONMATRIX_H */

