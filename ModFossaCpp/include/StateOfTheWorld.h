#ifndef STATEOFTHEWORLD_H_
#define STATEOFTHEWORLD_H_

#include <map>
#include <string>
#include <stdexcept>

#include <Concentration.h>

using std::map;
using std::string;

class StateOfTheWorld {
public:
    StateOfTheWorld();
    ~StateOfTheWorld();

    double getVoltage() const;
    double getConcentration(string ligand_name) const;

    void addConcentration(string ligand_name, double concentration_value);
    void setVoltage(double voltage);
//    void setConcentrations(map<string, Concentration*>&
//            concentrations);

private:
    double voltage;
    map<string, Concentration*>* concentrations;
    
    bool voltage_initialized;
};
#endif
