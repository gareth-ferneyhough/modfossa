/* 
 * File:   SigmoidalRateConstant.h
 * Author: gareth
 *
 * Created on February 19, 2013, 11:25 AM
 */

#ifndef SIGMOIDALRATECONSTANT_H_
#define	SIGMOIDALRATECONSTANT_H_

#include <ModelDefinition/RateConstantBase.h>
#include <string>
using std::string;

namespace ModelDefinition {

    class SigmoidalRateConstant : public RateConstantBase {
    public:
        SigmoidalRateConstant();
        SigmoidalRateConstant(string name, double a, double v_half, double k);
        virtual ~SigmoidalRateConstant();
        virtual double getRate(const shared_ptr<const StateOfTheWorld> state_of_the_world) const;

        string getName() const;
        void setName(string name);
        double getA() const;
        void setA(double a);
        double getVHalf() const;
        void setVHalf(double v_half);
        double getK() const;
        void setK(double k);

    private:
        string name;
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

