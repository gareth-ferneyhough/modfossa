#include <iostream>
#include <gtest/gtest.h>
#include <ModFossa/Experiment/SimulationRunner.h>

using namespace ModFossa;

class SimulationRunnerTest : public testing::Test {
protected:

    virtual void SetUp() {
        experiment = simulation_runner.getExperiment();
        markov_model = experiment->getMarkovModel();
    }

    virtual void TearDown() {
    }
    
    void createValidMarkovModel() {
        State::SharedPointer state_1(new State("state1", true));
        State::SharedPointer state_2(new State("state2", false));

        //RateConstantBase::SharedPointer rate1(new LigandGatedRateConstant(
        //        "rate1", "Ca", 2));
        
        RateConstantBase::SharedPointer 
            rate1(new ConstantRateConstant("rate1", 1));
        RateConstantBase::SharedPointer 
            rate2(new ConstantRateConstant("rate2", 10));
        
        
        Connection::SharedPointer connection1(
            new Connection("state1", "state2", "rate2"));
        Connection::SharedPointer connection2(
            new Connection("state2", "state1", "rate1"));


        markov_model->addState(state_2);
        markov_model->addState(state_1);
        markov_model->addRateConstant(rate1);
        markov_model->addRateConstant(rate2);
        markov_model->addConnection(connection1);
        markov_model->addConnection(connection2);
        markov_model->setInitialState("state1");
    }
    
    void addVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 500);

        // Add VoltageProtocol
        experiment->addVoltageProtocol(vp);
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
        experiment->addExperimentSweep(exp_sweep);
    }
    
    SimulationRunner simulation_runner;
    Experiment::SharedPointer experiment;
    MarkovModel::SharedPointer markov_model;
};

/**
 * Test Case X.1 - Run Sweep Success
 * Use Case: X.1 - Main Success Scenario
 */
TEST_F(SimulationRunnerTest, runSweepSuccess) {

    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addVoltageProtocol();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    // Validate Experiment
    experiment->validate();
       
    simulation_runner.runExperimentSweep("experiment sweep 1");
}


































