#include "StateOfTheWorld.h"

#include <iostream>


StateOfTheWorld::StateOfTheWorld(void) :
	voltage(-999),
	concentrations()
{
}


StateOfTheWorld::~StateOfTheWorld(void)
{
}

double StateOfTheWorld::GetVoltage() const
{
	return voltage;
}

double StateOfTheWorld::GetConcentration(string ligand_name) const
{
	if(concentrations->find(ligand_name) == concentrations->end())
    std::cout<<"Tim is not in the map!"<<endl;
}

void StateOfTheWorld::SetVoltage(double voltage)
{
	this->voltage = voltage;
}

void StateOfTheWorld::SetConcentrations(const map<string, Concentration>& concentrations)
{
	this->concentrations = &concentrations;
}