#ifndef CONSTANTRATECONSTANT_H_
#define CONSTANTRATECONSTANT_H_

#include <string>
#include <ModFossa/ModelDefinition/RateConstantBase.h>


namespace ModFossa {

class ConstantRateConstant : public RateConstantBase {
public:
    ConstantRateConstant(std::string name, double k);
    virtual ~ConstantRateConstant();
    virtual double getRate(
            const StateOfTheWorld::SharedPointer state_of_the_world) const;
    std::string getName() const;
    double getK() const;

private:
    const std::string name;
    const double k;
};
}
#endif
