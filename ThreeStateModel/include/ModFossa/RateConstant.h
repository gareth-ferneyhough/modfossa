/*
 * RateConstant.h
 *
 *  Created on: Jul 17, 2012
 *      Author: gareth
 */

#ifndef RATECONSTANT_H_
#define RATECONSTANT_H_

#include <string>

class RateConstant {
public:
    RateConstant();
    RateConstant(const RateConstant&);
    double getRate(double voltage);
    double getA() const;
    void setA(double a);
    double getK() const;
    void setK(double k);
    std::string getType() const;
    void setType(std::string type);
    double getVHalf() const;
    void setVHalf(double half);
    std::string getName() const;
    void setName(std::string name);

private:
    double getSigmoidalRate(double voltage);

    double k;
    double v_half;
    double a;
    std::string type;
    std::string name;
};

#endif /* RATECONSTANT_H_ */
