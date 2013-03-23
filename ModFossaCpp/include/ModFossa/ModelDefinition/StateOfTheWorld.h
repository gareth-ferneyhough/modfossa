#ifndef STATEOFTHEWORLD_H_
#define STATEOFTHEWORLD_H_

#include <map>
#include <string>
#include <stdexcept>

#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/ModelDefinition/Concentration.h>

namespace ModFossa {

class StateOfTheWorld {
public:
    typedef ModFossa::shared_ptr<StateOfTheWorld>::type SharedPointer;
    StateOfTheWorld();
    ~StateOfTheWorld();

    double getVoltage() const;
    bool concentrationExists(std::string ligand_name) const;
    double getConcentration(std::string ligand_name) const;

    void addConcentration(std::string ligand_name, double concentration_value);
    void setVoltage(double voltage);
    //    void setConcentrations(map<string, Concentration*>&
    //            concentrations);

private:
    double voltage;
    std::map<std::string, Concentration*>* concentrations;

    bool voltage_initialized;
};
}
#endif
