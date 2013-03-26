#include <string>
#include <stdexcept>
#include <gtest/gtest.h>
#include <ModFossa/Experiment/ExperimentSweep.h>

using namespace ModFossa;
using std::string;

class ExperimentSweepTest : public testing::Test {
protected:

    virtual void SetUp() {  

    }

    virtual void TearDown() {

    }
    
    ExperimentSweep* exp_sweep;
};

/**
 * Test Case XX.1 - Create ExperimentSweep success
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(ExperimentSweepTest, createSuccess) {
    string name = "exp sweep 1";
    string vp_name = "vp1";
    
    ExperimentSweep::ConcentrationMap map;
    
    exp_sweep = new ExperimentSweep(name, vp_name);//, map);
    ASSERT_EQ(exp_sweep->getName(), name);
    ASSERT_EQ(exp_sweep->getVoltageProtocolName(), vp_name);
}

/**
 * Test Case XX.1 - Create ExperimentSweep empty name
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(ExperimentSweepTest, createEmptyName) {   
    ExperimentSweep::ConcentrationMap map;
    
    ASSERT_THROW(exp_sweep = new ExperimentSweep("", "vp1"),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Create ExperimentSweep empty VoltageProtocol name
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(ExperimentSweepTest, createEmptyVoltageProtocolName) {   
    ExperimentSweep::ConcentrationMap map;
    
    ASSERT_THROW(exp_sweep = new ExperimentSweep("exp1", ""),
        std::runtime_error);
}









