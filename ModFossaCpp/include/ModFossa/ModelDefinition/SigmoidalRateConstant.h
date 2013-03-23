/* 
 * File:   SigmoidalRateConstant.h
 * Author: gareth
 *
 * Created on February 19, 2013, 11:25 AM
 */

#ifndef SIGMOIDALRATECONSTANT_H_
#define	SIGMOIDALRATECONSTANT_H_

#include <string>
#include <ModFossa/ModelDefinition/RateConstantBase.h>

namespace ModFossa {

class SigmoidalRateConstant : public RateConstantBase {
public:
    SigmoidalRateConstant();
    SigmoidalRateConstant(std::string name, double a, double v_half, double k);
    virtual ~SigmoidalRateConstant();
    virtual double getRate(
            const StateOfTheWorld::SharedPointer state_of_the_world) const;

    std::string getName() const;
    void setName(std::string name);
    double getA() const;
    void setA(double a);
    double getVHalf() const;
    void setVHalf(double v_half);
    double getK() const;
    void setK(double k);

private:
    std::string name;
    double a;
    double v_half;
    double k;

    bool name_initialized;
    bool a_initialized;
    bool v_half_initialized;
    bool k_initialized;
};
}
#endif	/* SIGMOIDALRATECONSTANT_H_ */

