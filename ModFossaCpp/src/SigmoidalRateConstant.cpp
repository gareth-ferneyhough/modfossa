/* 
 * File:   SigmoidalRateConstant.cpp
 * Author: gareth
 * 
 * Created on February 19, 2013, 11:25 AM
 */

#include <math.h>

#include <ModFossa/ModelDefinition/SigmoidalRateConstant.h>
#include <ModFossa/ModelDefinition/StateOfTheWorld.h>

namespace ModFossa {

SigmoidalRateConstant::SigmoidalRateConstant() :
RateConstantBase(),
name_initialized(false),
a_initialized(false),
v_half_initialized(false),
k_initialized(false) {
}

SigmoidalRateConstant::SigmoidalRateConstant(std::string name, double a,
        double v_half, double k) : RateConstantBase() {

    if (name.empty()) {
        throw std::runtime_error("Error: name is empty string");
    }
    this->name = name;
    this->a = a;
    this->v_half = v_half;
    this->k = k;

    name_initialized = true;
    a_initialized = true;
    v_half_initialized = true;
    k_initialized = true;
}

SigmoidalRateConstant::~SigmoidalRateConstant() {
}

double SigmoidalRateConstant::getRate(
    const StateOfTheWorld::SharedPointer state_of_the_world) const {
    if (!name_initialized) {
        throw std::runtime_error("name is not initialized");
    }
    if (!a_initialized) {
        throw std::runtime_error("a is not initialized");
    }
    if (!v_half_initialized) {
        throw std::runtime_error("v_half is not initialized");
    }
    if (!k_initialized) {
        throw std::runtime_error("k is not initialized");
    }
    if (state_of_the_world == NULL) {
        throw std::runtime_error("state_of_the_world is null");
    }

    double voltage = state_of_the_world->getVoltage();
    return (a) / (1 + exp((voltage - v_half) / k));
}

std::string SigmoidalRateConstant::getName() const {
    if (!name_initialized) {
        throw std::runtime_error("name is not initialized");
    }

    return name;
}

void SigmoidalRateConstant::setName(std::string name) {
    if (name.empty()) {
        throw std::runtime_error("Error: name is empty string");
    }

    this->name = name;
    name_initialized = true;
}

double SigmoidalRateConstant::getA() const {
    if (!a_initialized) {
        throw std::runtime_error("a is not initialized");
    }

    return a;
}

void SigmoidalRateConstant::setA(double a) {
    this->a = a;
    a_initialized = true;
}

double SigmoidalRateConstant::getVHalf() const {
    if (!v_half_initialized) {
        throw std::runtime_error("v_half is not initialized");
    }

    return v_half;
}

void SigmoidalRateConstant::setVHalf(double v_half) {

    this->v_half = v_half;
    v_half_initialized = true;
}

double SigmoidalRateConstant::getK() const {
    if (!k_initialized) {
        throw std::runtime_error("k is not initialized");
    }

    return k;
}

void SigmoidalRateConstant::setK(double k) {
    this->k = k;
    k_initialized = true;
}
}
