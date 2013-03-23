#ifndef CONCENTRATION_H_
#define CONCENTRATION_H_

#include <string>
#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {

struct Concentration {
    typedef ModFossa::shared_ptr<Concentration>::type SharedPointer;
    
    Concentration() {
    }

    Concentration(std::string ligand_name, double concentration_value) :
    ligand_name(ligand_name),
    concentration_value(concentration_value) {
    }

    std::string ligand_name;
    double concentration_value;
};
}

#endif