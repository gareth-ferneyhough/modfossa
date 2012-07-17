/*
 * RateConstant.cpp
 *
 *  Created on: Jul 17, 2012
 *      Author: gareth
 */

#include <iostream>
#include <cmath>

#include <ModFossa/RateConstant.h>

RateConstant::RateConstant() :
        k(0), v_half(0), a(0) {
}

RateConstant::RateConstant(const RateConstant& rhs) :
        k(rhs.k), v_half(rhs.v_half), a(rhs.a), type(rhs.type), name(rhs.name) {
}

double RateConstant::getA() const {
    return a;
}

void RateConstant::setA(double a) {
    this->a = a;
}

double RateConstant::getK() const {
    return k;
}

void RateConstant::setK(double k) {
    this->k = k;
}

std::string RateConstant::getType() const {
    return type;
}

void RateConstant::setType(std::string type) {
    if (type == "constant" || type == "sigmoidal") {
        this->type = type;
    } else {
        std::cout << "Error in RateConstant. Incorrect type requested.\n";
    }
}

double RateConstant::getVHalf() const {
    return v_half;
}

void RateConstant::setVHalf(double half) {
    v_half = half;
}

double RateConstant::getRate(double voltage) {
    double rate = 0;
    if (type == "constant") {
        rate = k;
    } else if (type == "sigmoidal") {
        rate = getSigmoidalRate(voltage);
    }

    return rate;
}

double RateConstant::getSigmoidalRate(double voltage) {
    double rate = a / (1 + exp((voltage - v_half) / k));
    return rate;
}

std::string RateConstant::getName() const {
    return name;
}

void RateConstant::setName(std::string name) {
    this->name = name;
}

