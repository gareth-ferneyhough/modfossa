#include <ModelDefinition/ConstantRateConstant.h>

#include <stdexcept>

namespace ModelDefinition{
ConstantRateConstant::ConstantRateConstant() :
RateConstantBase() {
}

ConstantRateConstant::ConstantRateConstant(string name, double k) :
RateConstantBase() {
    if (name.empty()) {
        throw std::runtime_error("Error: name cannot be empty string");
    }
    this->name = name;
    this->k = k;
}

ConstantRateConstant::~ConstantRateConstant() {
}

double ConstantRateConstant::getRate(StateOfTheWorld* state_of_the_world) {
    return k;
}

string ConstantRateConstant::getName() const {
    return name;
}

void ConstantRateConstant::setName(string name) {
    if (name.empty()) {
        throw std::runtime_error
                ("Error in setName: name cannot be empty string");
    }
    this-> name = name;
}

double ConstantRateConstant::getK() const {
    return k;
}

void ConstantRateConstant::setK(double k) {
    this->k = k;
}
}