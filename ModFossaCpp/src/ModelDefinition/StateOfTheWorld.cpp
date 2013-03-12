#include "ModelDefinition/StateOfTheWorld.h"

#include <iostream>

namespace ModelDefinition {

    StateOfTheWorld::StateOfTheWorld() :
    concentrations(),
    voltage_initialized(false) {
    }

    StateOfTheWorld::~StateOfTheWorld() {
        if (concentrations != NULL) {
            delete concentrations;
        }
    }

    double StateOfTheWorld::getVoltage() const {
        if (!voltage_initialized) {
            throw std::runtime_error("voltage not initialized");
        }

        return voltage;
    }

    double StateOfTheWorld::getConcentration(string ligand_name) const {
        // I dont like this:
        if (concentrations == NULL) {
            throw std::runtime_error("map of Concentrations not set");
        }

        map<string, Concentration*>::const_iterator it;
        it = concentrations->find(ligand_name);
        if (it == concentrations->end()) {
            throw std::runtime_error("no concentration defined for " + ligand_name);
        }

        return (it->second->concentration_value);
    }

    bool StateOfTheWorld::concentrationExists(string ligand_name) const {
        map<string, Concentration*>::const_iterator it;
        it = concentrations->find(ligand_name);
        if (it == concentrations->end()) {
            return false;
        } else {
            return true;
        }
    }

    void StateOfTheWorld::addConcentration(string ligand_name,
            double concentration_value) {
        if (concentrations == NULL) {
            concentrations = new map<string, Concentration*>();
        }

        (*concentrations)[ligand_name] = new Concentration(ligand_name,
                concentration_value);
    }

    void StateOfTheWorld::setVoltage(double voltage) {
        voltage_initialized = true;
        this->voltage = voltage;
    }

    //void StateOfTheWorld::setConcentrations(map<string, Concentration*>&
    //        concentrations) {
    //    if (this->concentrations != NULL) {
    //        delete this->concentrations;
    //    }
    //
    //    this->concentrations = &concentrations;
    //}
}