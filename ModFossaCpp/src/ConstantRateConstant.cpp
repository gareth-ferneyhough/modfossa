#include <ModelDefinition/ConstantRateConstant.h>

#include <stdexcept>

namespace ModelDefinition {

    ConstantRateConstant::ConstantRateConstant(string name, double k) :
    RateConstantBase(),
    name(name),
    k(k) {
        if (name.empty()) {
            throw std::runtime_error("Error: name cannot be empty string");
        }
    }

    ConstantRateConstant::~ConstantRateConstant() {
    }

    double ConstantRateConstant::getRate(
        const StateOfTheWorld::SharedPointer state_of_the_world) const {
        return k;
    }

    string ConstantRateConstant::getName() const {
        return name;
    }

    double ConstantRateConstant::getK() const {
        return k;
    }
}