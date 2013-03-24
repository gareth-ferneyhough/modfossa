#include <string>
#include <stdexcept>
#include <gtest/gtest.h>
#include <ModFossa/Experiment/VoltageProtocol.h>

using namespace ModFossa;
using std::string;

class VoltageProtocolTest : public testing::Test {
protected:

    virtual void SetUp() {  

    }

    virtual void TearDown() {

    }
    
    VoltageProtocol* vp;
};

/**
 * Test Case XX.1 - Create VoltageProtocol success
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, createSuccess) {
    string name = "voltage_protocol1";
    vp = new VoltageProtocol(name);
    ASSERT_EQ(vp->getName(), name);
}

/**
 * Test Case XX.1 - Create VoltageProtocol empty name
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, createEmptyName) {
    ASSERT_THROW(vp = new VoltageProtocol(""),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Add constant stage success
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, addConstantStageSuccess) {
    vp = new VoltageProtocol("vp1");
    vp->addConstantStage("stage1", -50, 200);
}

/**
 * Test Case XX.1 - Add constant stage empty name
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addConstantStageEmptyName) {
    vp = new VoltageProtocol("vp1");
    ASSERT_THROW(vp->addConstantStage("", -50, 200),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Add constant stage non-positive duration
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addConstantStageNonPositiveDuration) {
    vp = new VoltageProtocol("vp1");
    ASSERT_THROW(vp->addConstantStage("stage1", -50, 0),
        std::runtime_error);
    
    ASSERT_THROW(vp->addConstantStage("stage1", -50, -1),
        std::runtime_error);
}
















































