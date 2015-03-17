#ifndef STATEOFTHEWORLD_H_
#define STATEOFTHEWORLD_H_

#include <map>
#include <string>
#include <stdexcept>

#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Common/Concentration.h>

namespace ModFossa {

class StateOfTheWorld {
public:
    typedef ModFossa::shared_ptr<StateOfTheWorld>::type SharedPointer;
    typedef std::map<std::string, Concentration::SharedPointer>ConcentrationMap;
    
    StateOfTheWorld(ConcentrationMap concentrations);
    ~StateOfTheWorld();

    double getVoltage() const;
    bool concentrationExists(std::string ligand_name) const;
    double getConcentration(std::string ligand_name) const;

    void setVoltage(double voltage);
    
private:
    double voltage;
    bool voltage_initialized;
    ConcentrationMap concentrations;
};
}
#endif
