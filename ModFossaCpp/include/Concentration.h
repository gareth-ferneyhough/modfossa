#ifndef CONCENTRATION_H_
#define CONCENTRATION_H_

#include <string>
using std::string;

struct Concentration
{
	Concentration() {}
	Concentration(string ligand_name, double concentration_value) : 
        ligand_name(ligand_name), 
        concentration_value(concentration_value) {}
        
	string ligand_name;
	double concentration_value;
};

#endif