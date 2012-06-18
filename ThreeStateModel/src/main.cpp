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


#include <boost/python.hpp>
#include <pyublas/numpy.hpp>

#include "Model.h"

//using namespace boost::numeric::ublas;
using namespace ModFossa;



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
	Model* model = Model::getInstance();

	model->addState("C1");
	model->addState("C2");
	model->addState("O");

	int kon1 = 1;
	int koff1 = 100;
	int kon2 = 1;
	int koff2 = 100;

	model->connect("C1", "C2", kon1);
	model->connect("C2", "C1", koff1);
	model->connect("C2", "O", kon2);
	model->connect("O", "C2", koff2);

	model->setInitialState("O");
	model->setTspan(drange(0, 0.001, 0.1));

	return model->run();
}

//pyublas::numpy_matrix<double> solve() {
//
//	std::vector<double> tspan = drange(0, 0.001, 0.1);
//	matrix<double> result;
//	std::vector<double> initial_conditions;
//
//	/* Initial conditions. Start in open state.
//	 * pC1(0) = 0
//	 * pC2(0) = 0
//	 * pO(0)  = 1
//	 */
//
//	initial_conditions.push_back(0);
//	initial_conditions.push_back(0);
//	initial_conditions.push_back(1);
//
//	SundialsCpp open_solver;
//	open_solver.solve(channelProb, tspan, initial_conditions, result);
//
//	// Implicitly convert result to pyublas::numpy_matrix
//	return result;
//}
//
BOOST_PYTHON_MODULE(libModFossa) {
	using namespace boost::python;
	def("solve", solve);
}
