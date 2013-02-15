#ifndef _STATEOFTHEWORLD_H
#define _STATEOFTHEWORLD_H

#include <map>
#include <string>

#include <Concentration.h>

using std::map;
using std::string;

class StateOfTheWorld
{
public:
	StateOfTheWorld();
	~StateOfTheWorld();

	double GetVoltage() const;
	double GetConcentration(string ligand_name) const;

	void SetVoltage(double voltage);
	void SetConcentrations(const map<string, Concentration>& concentrations);

private:
	double voltage;
	const map<string, Concentration>* concentrations;
};
#endif
