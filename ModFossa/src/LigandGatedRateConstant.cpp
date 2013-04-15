/* 
 * File:   LigandGatedRateConstant.cpp
 * Author: gareth
 * 
 * Created on February 19, 2013, 11:25 AM
 */

#include <ModFossa/ModelDefinition/LigandGatedRateConstant.h>
#include <ModFossa/Common/StateOfTheWorld.h>

#include <math.h>

namespace ModFossa {

    LigandGatedRateConstant::LigandGatedRateConstant(
            std::string name, double k, 
            std::string ligand_name, double ligand_power) :
    RateConstantBase(),
    name(name),
    k(k),
    ligand_name(ligand_name),
    ligand_power(ligand_power) {

        if (name.empty()) {
            throw std::runtime_error("LigandGatedRateConstant name cannot be empty");
        }

        if (ligand_name.empty()) {
            throw std::runtime_error("ligand_name cannot be empty");
        }
    }

    LigandGatedRateConstant::~LigandGatedRateConstant() {
    }

    double LigandGatedRateConstant::getRate(
        const StateOfTheWorld::SharedPointer state_of_the_world) const {
        if (state_of_the_world == NULL) {
            throw std::runtime_error(
                    "Error in getRate for " + name +
                    ": state_of_the_world cannot be NULL");
        }

        // Fix rate
        try {
            double concentration = state_of_the_world->getConcentration(ligand_name);
            return k*pow(concentration, ligand_power);
            
        } catch (std::runtime_error& e) {
            throw std::runtime_error("Error in getRate for " + name + ": " + e.what());
        }
    }

    std::string LigandGatedRateConstant::getName() const {
        return name;
    }

    std::string LigandGatedRateConstant::getLigandName() const {
        return ligand_name;
    }

    double LigandGatedRateConstant::getLigandPower() const {
        return ligand_power;
    }
}
