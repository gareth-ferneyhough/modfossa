#include <iostream>
#include <gtest/gtest.h>
#include <ModFossa/Experiment/Experiment.h>

using namespace ModFossa;
using namespace Validation;

class ExperimentTest : public testing::Test {
protected:

    virtual void SetUp() {
        markov_model = experiment.getMarkovModel();
    }

    virtual void TearDown() {
    }
    
    void createValidMarkovModel() {
        State::SharedPointer state_1(new State("state1", true));
        State::SharedPointer state_2(new State("state2", false));

        RateConstantBase::SharedPointer rate1(new LigandGatedRateConstant(
                "rate1", "Ca", 2));
        Connection::SharedPointer connection(
            new Connection("state1", "state2", "rate1"));

        markov_model->addState(state_1);
        markov_model->addState(state_2);
        markov_model->addRateConstant(rate1);
        markov_model->addConnection(connection);
        markov_model->setInitialState("state1");
    }
    
    void addVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 200);

        // Add VoltageProtocol
        experiment.addVoltageProtocol(vp);
    }
    
    void addExperimentSweep() {
        // Define ConcentrationMap
        ExperimentSweep::ConcentrationMap concentrations;
        concentrations["Ca"] = Concentration::SharedPointer(
                new Concentration("Ca", 2.0));
        
        ExperimentSweep::SharedPointer exp_sweep(new ExperimentSweep(
            "experiment sweep 1", 
            "voltage protocol 1", 
            concentrations));

        // Add ExperimentSweep
        experiment.addExperimentSweep(exp_sweep);
    }
    
    bool errorExists(ValidationResults::ErrorVector errors, 
        int error_type) {
        
        ValidationResults::ErrorVector::const_iterator it;
        for(it = errors.begin(); it < errors.end(); ++it) {
            if(it->first == error_type) {
                return true;
            }
        }
        return false;        
    }

    Experiment experiment;
    MarkovModel::SharedPointer markov_model;
};

/**
 * Test Case X.1 - Validate Experiment Success
 * Use Case: X.1 - Main Success Scenario
 */
TEST_F(ExperimentTest, validateExperimentSuccess) {

    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addVoltageProtocol();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    ValidationResults results = experiment.validate();   
    ASSERT_TRUE(results.overall_result == NO_WARNINGS);    
}

/**
 * Test Case X.1 - Validate Experiment no VoltageProtocol
 * Use Case: X.1 - Extention X.X
 */
TEST_F(ExperimentTest, validateExperimentNoVoltageProtocol) {
    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    // Do not add a VoltageProtocol
    
    ValidationResults results = experiment.validate();   
    ASSERT_TRUE(errorExists(results.errors, NO_VOLTAGE_PROTOCOLS));
    ASSERT_TRUE(results.overall_result == ERRORS);      
}

/**
 * Test Case X.1 - Validate Experiment no ExperimentSweep
 * Use Case: X.1 - Extention X.X
 */
TEST_F(ExperimentTest, validateExperimentNoExperimentSweep) {
    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addVoltageProtocol();
    
    // Do not add an ExperimentSweep
        
    ValidationResults results = experiment.validate();   
    ASSERT_TRUE(errorExists(results.errors, NO_EXPERIMENT_SWEEPS));
    ASSERT_TRUE(results.overall_result == ERRORS);      
}

















































