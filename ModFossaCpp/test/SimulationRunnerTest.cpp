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
            rate2(new ConstantRateConstant("rate2", 100));
        
//        RateConstantBase::SharedPointer 
//            rate2(new ExponentialRateConstant("rate2", 1, 2));
        
        
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
        markov_model->setMaxChannelConductance(1);
        markov_model->setReversalPotential(1);
        markov_model->setMembraneCapacitance(100);
    }
    
    void addVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 500);

        // Add VoltageProtocol
        experiment->addVoltageProtocol(vp);
    }
    
    void addSteppedVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 500);
        vp->addSteppedStage("step1", -80, 40, 20, 500);

        // Add VoltageProtocol
        experiment->addVoltageProtocol(vp);
    }
    
     void addShortVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 1);
        vp->addConstantStage("hold2", -80, 2);
        vp->addConstantStage("hold2", -80, 3);
        vp->addConstantStage("hold1", -80, 4);
        vp->addConstantStage("hold2", -80, 5);
        vp->addConstantStage("hold2", -80, 6);
        vp->addConstantStage("hold1", -80, 7);
        vp->addConstantStage("hold2", -80, 8);
        vp->addConstantStage("hold2", -80, 9);
        vp->addConstantStage("hold2", -80, 10);

        // Add VoltageProtocol
        experiment->addVoltageProtocol(vp);
    }
     
    void addLongVoltageProtocol() {
        // Define VoltageProtocol
        VoltageProtocol::SharedPointer vp(
            new VoltageProtocol("voltage protocol 1"));

        vp->addConstantStage("hold1", -80, 1100);
        vp->addConstantStage("hold2", -80, 1101);
        vp->addConstantStage("hold2", -80, 1102);
        vp->addConstantStage("hold1", -80, 1103);
        vp->addConstantStage("hold2", -80, 1104);
        vp->addConstantStage("hold2", -80, 1105);
        
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
            "voltage protocol 1"));
        
        exp_sweep->addConcentration(Concentration("Ca", 2.0));

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
       
    simulation_runner.runAllExperimentSweeps();
}

/**
 * Test Case X.1 - Run Stepped Sweep Success
 * Use Case: X.1 - Main Success Scenario
 */
TEST_F(SimulationRunnerTest, runSteppedSweepSuccess) {
    
    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addSteppedVoltageProtocol();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    // Validate Experiment
    experiment->validate();
       
    simulation_runner.runAllExperimentSweeps();
}

/**
 * Test Case X.1 - Test results length
 * Use Case: X.1 - Main Success Scenario
 * 
 * Test that the size of the output is correct given various (short) voltage
 * hold stages.
 */
TEST_F(SimulationRunnerTest, testResultsLength) {
    
    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addShortVoltageProtocol();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    // Validate Experiment
    experiment->validate();
      
    simulation_runner.runAllExperimentSweeps();   
    
    Results::SharedPointer results = simulation_runner.getResultsClass();
    
    Vector2d currents = results->getCurrents("experiment sweep 1");
    ASSERT_EQ(currents.front().size(), (unsigned int)55);
}

/**
 * Test Case X.1 - Test results length 2
 * Use Case: X.1 - Main Success Scenario
 * 
 * Test that the size of the output is correct given various (long) voltage
 * hold stages.
 */
TEST_F(SimulationRunnerTest, testResultsLength2) {
    
    // Create a valid MarkovModel with a rate dependent on Ca
    createValidMarkovModel();
    
    // Add valid VoltageProtocol
    addLongVoltageProtocol();
    
    // Add ExperimentSweep with a concentration defined for Ca
    addExperimentSweep();
    
    // Validate Experiment
    experiment->validate();
      
    simulation_runner.runAllExperimentSweeps();   
    
    Results::SharedPointer results = simulation_runner.getResultsClass();
    
    Vector2d currents = results->getCurrents("experiment sweep 1");
    ASSERT_EQ(currents.front().size(), (unsigned int)6615);
}





























