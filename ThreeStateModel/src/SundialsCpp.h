/*
 * SundialsCpp.h
 *
 *  Created on: May 30, 2012
 *      Author: gareth
 */

#ifndef SUNDIALSCPP_H_
#define SUNDIALSCPP_H_

#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <cvode/cvode_dense.h>
#include <sundials/sundials_dense.h>
#include <sundials/sundials_types.h>

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "SundialsCpp.h"

using namespace boost::numeric::ublas;

class SundialsCpp {
public:
	SundialsCpp();
	virtual ~SundialsCpp();
	int solve(CVRhsFn, std::vector<double> tspan, std::vector<double> y0, matrix<double>& y);

private:
	void init();

	realtype reltol; //= 1e-6;
	realtype abstol; //= 1e-8;
	void* cvode_mem;
};

#endif /* SUNDIALSCPP_H_ */

