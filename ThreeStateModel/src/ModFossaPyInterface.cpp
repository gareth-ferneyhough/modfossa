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

#include <ModFossa/Model.h>
#include <ModFossa/Util.h>

using namespace ModFossa;

void addState(std::string name) {
    Model::getInstance()->addState(name);
}

void setConducting(std::string name) {
    Model::getInstance()->setConducting(name);
}

void connect(std::string in, std::string out, double rate) {
    Model::getInstance()->connect(in, out, rate);
}

void setInitialState(std::string name) {
    Model::getInstance()->setInitialState(name);
}

void setIntegrationWindow(double first, double increment, double last) {
    Model::getInstance()->setIntegrationWindow(drange(first, increment, last));
}

pyublas::numpy_matrix<double> run() {
    return Model::getInstance()->run();
}

BOOST_PYTHON_MODULE(libModFossa) {
    using namespace boost::python;
    def("addState", addState);
    def("setConducting", setConducting);
    def("connect", connect);
    def("setInitialState", setInitialState);
    def("setIntegrationWindow", setIntegrationWindow);
    def("run", run);
}
