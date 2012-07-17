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

void connect(std::string in, std::string out, std::string rate_constant) {
    Model::getInstance()->connect(in, out, rate_constant);
}

void setInitialState(std::string name) {
    Model::getInstance()->setInitialState(name);
}

void setIntegrationWindow(double first, double increment, double last) {
    Model::getInstance()->setIntegrationWindow(drange(first, increment, last));
}

void setVstep(double first, double increment, double last) {
    Model::getInstance()->setVstep(drange(first, increment, last));
}

void setVholdStart(double v_hold_start) {
    Model::getInstance()->setVholdStart(v_hold_start);
}

void setVholdFinish(double v_hold_finish) {
    Model::getInstance()->setVholdFinish(v_hold_finish);
}

void setEventTimes(double start, double step, double finish, double end) {
    Model::getInstance()->setEventTimes(start, step, finish, end);
}

pyublas::numpy_matrix<double> run() {
    return Model::getInstance()->run();
}

pyublas::numpy_matrix<double> getVoltageProtocol() {
    return Model::getInstance()->getVoltageProtocol();
}

void addRateConstant(std::string type, double k, double a, double v_half,
        std::string name) {
    Model::getInstance()->addRateConstant(type, a, v_half, k, name);
}

//void addRateConstant(std::string type, double k, std::string name) {
//    if(type != "constant") {
//        std::cout << "Error adding rate constant. Only constant rate constants can have one parameter.\n";
//    }
//    else {
//        Model::getInstance()->addRateConstant(type, k, name);
//    }
//}

BOOST_PYTHON_MODULE(libModFossa)
{
    using namespace boost::python;
    def("addState", addState);
    def("setConducting", setConducting);
    def("connect", connect);
    def("setInitialState", setInitialState);
    def("setIntegrationWindow", setIntegrationWindow);
    def("setVstep", setVstep);
    def("setVholdStart", setVholdStart);
    def("setVholdFinish", setVholdFinish);
    def("setEventTimes", setEventTimes);
    def("run", run);
    def("getVoltageProtocol", getVoltageProtocol);
    def("addRateConstant", addRateConstant);
}
