/* 
 * File:   LigandGatedRateConstant.h
 * Author: gareth
 *
 * Created on February 19, 2013, 11:25 AM
 */

#ifndef LIGANDGATEDRATECONSTANT_H_
#define	LIGANDGATEDRATECONSTANT_H_

#include <ModelDefinition/RateConstantBase.h>
#include <string>
using std::string;

namespace ModelDefinition {

    class LigandGatedRateConstant : public RateConstantBase {
    public:
        LigandGatedRateConstant(string name, string ligand_name, double ligand_power);
        virtual ~LigandGatedRateConstant();
        virtual double getRate(const shared_ptr<const StateOfTheWorld> state_of_the_world) const;

        virtual string getName() const;
		string getLigandName() const;
		double getLigandPower() const;

    private:
        const string name;
		const string ligand_name;
		const double ligand_power;
    };
}
#endif	/* LIGANDGATEDRATECONSTANT_H_ */

