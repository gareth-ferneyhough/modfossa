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

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <ModFossa/Common/Matrix.h>

//using namespace boost::numeric::ublas;

namespace ModFossa {
class ODESolver {
public:
    ODESolver();
    ~ODESolver();
    
    void initialize(Matrix transition_matrix);
        
    int solve(CVRhsFn, std::vector<double> tspan, std::vector<double> y0,
            Matrix& y);

private:
    void init();

    realtype reltol; //= 1e-6;
    realtype abstol; //= 1e-8;
    void* cvode_mem;
};
}

#endif /* ODESOLVER_H_H */

