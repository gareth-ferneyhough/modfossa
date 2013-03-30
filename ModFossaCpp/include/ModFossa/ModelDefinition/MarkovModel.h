#ifndef MARKOVMODEL_H_
#define MARKOVMODEL_H_

#include <vector>
#include <map>
#include <string>

#include <ModFossa/ModelDefinition/RateConstantBase.h>
#include <ModFossa/ModelDefinition/ConstantRateConstant.h>
#include <ModFossa/ModelDefinition/LigandGatedRateConstant.h>
#include <ModFossa/ModelDefinition/SigmoidalRateConstant.h>
#include <ModFossa/ModelDefinition/ExponentialRateConstant.h>
#include <ModFossa/ModelDefinition/State.h>
#include <ModFossa/ModelDefinition/Connection.h>
#include <ModFossa/Common/Validation/ValidationResults.h>
#include <ModFossa/Common/StateOfTheWorld.h>
#include <ModFossa/Common/Concentration.h>
#include <ModFossa/Common/ContainerTypes.h>

namespace ModFossa {

class MarkovModel {
public:
    typedef ModFossa::shared_ptr<MarkovModel>::type SharedPointer;
    typedef std::map<std::string, RateConstantBase::SharedPointer > 
        RateMap;
    typedef std::map<std::string, State::SharedPointer > StateMap;
    typedef std::vector<Connection::SharedPointer > ConnectionsVector;

    MarkovModel();
    ~MarkovModel();

    void addState(const State::SharedPointer state);
    void addRateConstant(
            const RateConstantBase::SharedPointer rate_constant);
    void addConnection(const Connection::SharedPointer connection);
    void setInitialState(std::string initial_state);
    void setMaxChannelConductance(double max_channel_conductance);
    void setReversalPotential(double reversal_potential);
    
    Validation::ValidationResults validate(
            const StateOfTheWorld::SharedPointer state_of_the_world);
    
    double getReversalPotential() const;
    double getMaxChannelConductance() const;
    VectorSharedPtr getStateGatingVariables() const;
    StringVecSharedPtr getStateNames() const;
    
    bool isValid() const;

private:
    bool is_valid;
    std::string initial_state;
    double max_channel_conductance;
    double reversal_potential;

    RateMap map_of_rates;
    StateMap map_of_states;
    ConnectionsVector connections;

    bool stateExists(std::string name) const;
    bool rateConstantExists(std::string name) const;
    bool connectionExists(std::string from_state, std::string to_state) const;

    friend class TransitionMatrix;
};
}

#endif
