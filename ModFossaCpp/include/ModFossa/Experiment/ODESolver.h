/*
 * ODESolver.h
 *
 *  Created on: March 24, 2013
 *      Author: gareth
 */

#ifndef ODESOLVER_H_H
#define ODESOLVER_H_H

#include <cstdio>
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <cvode/cvode_dense.h>
#include <sundials/sundials_dense.h>
#include <sundials/sundials_types.h>

#include <vector>

//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>

#include <ModFossa/Common/Matrix.h>
#include <ModFossa/Common/SharedPtr.h>

//using namespace boost::numeric::ublas;

namespace ModFossa {
class ODESolver {
public:
    typedef shared_ptr<Matrix>::type MatrixSharedPointer;
    
    ODESolver();
    ~ODESolver();
    
    int initialize(std::vector<double> initial_conditions);
        
    int solve(std::vector<double> tspan, 
        MatrixSharedPointer transition_matrix, Matrix& y);
    
    static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot, 
        void *f_data);

private:
    void init();
    
    MatrixSharedPointer transition_matrix;
    
    const realtype reltol = 1e-6;
    const realtype abstol = 1e-8;
    void* cvode_mem;
    N_Vector y_n_vector;
    int y_size;
};
}

#endif /* ODESOLVER_H_H */

