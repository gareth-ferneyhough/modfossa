#include <iostream>
#include <ModFossa/Common/StateOfTheWorld.h>

using std::string;
using std::map;

namespace ModFossa {

StateOfTheWorld::StateOfTheWorld(ConcentrationMap concentrations) :
voltage_initialized(false),
concentrations(concentrations)
{
}

StateOfTheWorld::~StateOfTheWorld() {
}

double StateOfTheWorld::getVoltage() const {
    if (!voltage_initialized) {
        throw std::runtime_error("voltage not initialized");
    }

    return voltage;
}

double StateOfTheWorld::getConcentration(string ligand_name) const {
    ConcentrationMap::const_iterator it;
    it = concentrations.find(ligand_name);
    if (it == concentrations.end()) {
        throw std::runtime_error("no concentration defined for " + ligand_name);
    }

    return (it->second->concentration_value);
}

bool StateOfTheWorld::concentrationExists(string ligand_name) const {
    ConcentrationMap::const_iterator it;
    it = concentrations.find(ligand_name);
    if (it == concentrations.end()) {
        return false;
    } else {
        return true;
    }
}

void StateOfTheWorld::setVoltage(double voltage) {
    voltage_initialized = true;
    this->voltage = voltage;
}
}