#ifndef _MARKOVMODEL_H
#define _MARKOVMODEL_H

#include <map>
#include <string>

using std::string;
using std::map;

class State;
class RateConstantBase;
class ModelDescription;
class ConnectionManager;

/**
 * Class responsible for creating and storing information required to
 * describe a markov model for an ion channel. The user adds RateConstants
 * and States using the methods provided. After the model is described,
 * the user calls BuildConnections(). At this point the ConnectionManager and 
 * ModelDescription are used to create the transitionMatrix, which is 
 * used to run the simulation.
 */
class MarkovModel {
public:
	MarkovModel();
	~MarkovModel();

	void AddState(string name, bool conducting, bool initial=false);

	void AddConstantRateConstant(string name, double k);

	void AddSigmoidalRateConstant(string name, double a, double vHalf,
			double k);

	void AddLigandDependentRateConstant(string name, double k,
			double ligandPower, string ligandAbbreviation);

	void AddExponentialRateConstant(string name, double a, double k);

	void AddBolztmannRateConstant(string name, double a, double a2,
			double vHalf, double k);

        void BuildConnections();

private:
	map<string, RateConstantBase*> mapOfRates;
	map<string, State*> mapOfStates;

	ModelDescription* modelDescription;
	ConnectionManager* connectionManager;
};

#endif
