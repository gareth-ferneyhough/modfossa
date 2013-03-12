#ifndef STATEOFTHEWORLD_H_
#define STATEOFTHEWORLD_H_

#include <map>
#include <string>
#include <stdexcept>
#include <memory>

#include <ModelDefinition/Concentration.h>

using std::map;
using std::string;
using std::shared_ptr;

namespace ModelDefinition {

    class StateOfTheWorld {
    public:
        typedef shared_ptr<const StateOfTheWorld> SharedPointer;
        StateOfTheWorld();
        ~StateOfTheWorld();

        double getVoltage() const;
        bool concentrationExists(string ligand_name) const;
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
}
#endif
