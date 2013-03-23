/* 
 * File:   LigandGatedRateConstant.h
 * Author: gareth
 *
 * Created on February 19, 2013, 11:25 AM
 */

#ifndef LIGANDGATEDRATECONSTANT_H_
#define	LIGANDGATEDRATECONSTANT_H_


#include <string>
#include <ModFossa/Common/StateOfTheWorld.h>
#include <ModFossa/ModelDefinition/RateConstantBase.h>


namespace ModFossa {

class LigandGatedRateConstant : public RateConstantBase {
public:
    LigandGatedRateConstant(std::string name, std::string ligand_name, 
            double ligand_power);
    virtual ~LigandGatedRateConstant();
    virtual double getRate(const StateOfTheWorld::SharedPointer 
            state_of_the_world) const;

    virtual std::string getName() const;
    std::string getLigandName() const;
    double getLigandPower() const;

private:
    const std::string name;
    const std::string ligand_name;
    const double ligand_power;
};
}
#endif	/* LIGANDGATEDRATECONSTANT_H_ */

