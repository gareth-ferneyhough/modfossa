#ifndef CONSTANTRATECONSTANT_H_
#define CONSTANTRATECONSTANT_H_

#include <string>

#include <RateConstantBase.h>

using std::string;

class ConstantRateConstant : public RateConstantBase {
public:
    ConstantRateConstant();
    ConstantRateConstant(string name, double k);
    virtual ~ConstantRateConstant();
    virtual double getRate(StateOfTheWorld* stateOfTheWorld);
    string getName() const;
    void setName(string name);
    double getK() const;
    void setK(double k);

private:
    string name;
    double k;
};
#endif
