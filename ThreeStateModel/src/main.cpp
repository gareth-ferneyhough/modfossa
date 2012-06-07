/*
 * main.cpp
 *
 *  Created on: May 30, 2012
 *      Author: gareth
 */

#include <assert.h>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/python.hpp>
#include <pyublas/numpy.hpp>

#include "SundialsCpp.h"

using namespace boost::numeric::ublas;

static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
		void *f_data) {
	/* y(0) = PC1
	 * y(1) = PC2
	 * y(2) = PO
	 */

	int kon1 = 1;
	int koff1 = 100;
	int kon2 = 1;
	int koff2 = 100;

	double pC1 = NV_Ith_S(y_vec, 0);
	double pC2 = NV_Ith_S(y_vec, 1);
	double pO  = NV_Ith_S(y_vec, 2);

	double pC1_dot = -kon1 * pC1 + koff1 * pC2;
	double pC2_dot = -koff1 * pC2 + kon1 * pC1 -kon2 * pC2 + koff2 * pO;
	double pO_dot  = -koff2 * pO + kon2 * pC2;

	NV_Ith_S(ydot, 0) = pC1_dot;
	NV_Ith_S(ydot, 1) = pC2_dot;
	NV_Ith_S(ydot, 2) = pO_dot;

	return 0;
}

/* Function: drange
 *
 * Generates and returns an stl vector of doubles in the range given by
 * first, increment, and last (inclusive).
 *
 */
std::vector<double> drange(double first, double increment, double last) {
	std::vector<double> range;

	double t = first;
	while (t <= last) {
		range.push_back(t);
		t += increment;
	}

	return range;
}

pyublas::numpy_matrix<double> solve() {

	std::vector<double> tspan = drange(0, 0.001, 0.1);
	matrix<double> result;
	std::vector<double> initial_conditions;

	/* Initial conditions. Start in open state.
	 * pC1(0) = 0
	 * pC2(0) = 0
	 * pO(0)  = 1
	 */

	initial_conditions.push_back(0);
	initial_conditions.push_back(0);
	initial_conditions.push_back(1);

	SundialsCpp open_solver;
	open_solver.solve(channelProb, tspan, initial_conditions, result);

	// Implicitly convert result to pyublas::numpy_matrix
	return result;
}

BOOST_PYTHON_MODULE(libModFossa) {
	using namespace boost::python;
	def("solve", solve);
}
