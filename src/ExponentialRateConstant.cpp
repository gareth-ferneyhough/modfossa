/* 
 * File:   ExponentialRateConstant.cpp
 * Author: gareth
 *
 * Created on March 28, 2013, 11:25 AM
 */

#include <math.h>

#include <ModFossa/ModelDefinition/ExponentialRateConstant.h>
#include <ModFossa/Common/StateOfTheWorld.h>

namespace ModFossa {

ExponentialRateConstant::ExponentialRateConstant() :
RateConstantBase(),
name_initialized(false),
a_initialized(false),
k_initialized(false) {
}

ExponentialRateConstant::ExponentialRateConstant(std::string name, double a, 
        double k) : RateConstantBase() {

    if (name.empty()) {
        throw std::runtime_error("Error: name is empty string");
    }
    this->name = name;
    this->a = a;
    this->k = k;

    name_initialized = true;
    a_initialized = true;
    k_initialized = true;
}

ExponentialRateConstant::~ExponentialRateConstant() {
}

double ExponentialRateConstant::getRate(
    const StateOfTheWorld::SharedPointer state_of_the_world) const {
    if (!name_initialized) {
        throw std::runtime_error("name is not initialized");
    }
    if (!a_initialized) {
        throw std::runtime_error("a is not initialized");
    }
    if (!k_initialized) {
        throw std::runtime_error("k is not initialized");
    }
    if (state_of_the_world == NULL) {
        throw std::runtime_error("state_of_the_world is null");
    }

    double voltage = state_of_the_world->getVoltage();
    return (a * exp(k * voltage));
}

std::string ExponentialRateConstant::getName() const {
    if (!name_initialized) {
        throw std::runtime_error("name is not initialized");
    }

    return name;
}

void ExponentialRateConstant::setName(std::string name) {
    if (name.empty()) {
        throw std::runtime_error("Error: name is empty string");
    }

    this->name = name;
    name_initialized = true;
}

double ExponentialRateConstant::getA() const {
    if (!a_initialized) {
        throw std::runtime_error("a is not initialized");
    }

    return a;
}

void ExponentialRateConstant::setA(double a) {
    this->a = a;
    a_initialized = true;
}

double ExponentialRateConstant::getK() const {
    if (!k_initialized) {
        throw std::runtime_error("k is not initialized");
    }

    return k;
}

void ExponentialRateConstant::setK(double k) {
    this->k = k;
    k_initialized = true;
}
}
