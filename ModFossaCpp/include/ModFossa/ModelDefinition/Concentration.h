#ifndef CONCENTRATION_H_
#define CONCENTRATION_H_

#include <string>

namespace ModFossa {

struct Concentration {

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