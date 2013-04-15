/* 
 * File:   ExponentialRateConstant.h
 * Author: gareth
 *
 * Created on March 28, 2013, 11:25 AM
 */

#ifndef EXPONENTIALRATECONSTANT_H_
#define	EXPONENTIALRATECONSTANT_H_

#include <string>
#include <ModFossa/ModelDefinition/RateConstantBase.h>

namespace ModFossa {

class ExponentialRateConstant : public RateConstantBase {
public:
    ExponentialRateConstant();
    ExponentialRateConstant(std::string name, double a, double k);
    virtual ~ExponentialRateConstant();
    virtual double getRate(
            const StateOfTheWorld::SharedPointer state_of_the_world) const;

    std::string getName() const;
    void setName(std::string name);
    double getA() const;
    void setA(double a);
    double getK() const;
    void setK(double k);

private:
    std::string name;
    double a;
    double k;

    bool name_initialized;
    bool a_initialized;
    bool k_initialized;
};
}
#endif	/* EXPONENTIALRATECONSTANT_H_ */

