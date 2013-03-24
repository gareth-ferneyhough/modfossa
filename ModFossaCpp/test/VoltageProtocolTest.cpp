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

/**
 * Test Case XX.1 - Add stepped stage success
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, addSteppedStageSuccess) {
    vp = new VoltageProtocol("vp1");
    
    vp->addSteppedStage("step1", -50, 30, 20, 200);
}

/**
 * Test Case XX.1 - Add stepped stage empty name
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addSteppedStageEmptyName) {
    vp = new VoltageProtocol("vp1");
    ASSERT_THROW(vp->addSteppedStage("", -50, 30, 20, 200),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Add stepped stage non-positive duration
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addSteppedStageNonPositiveDuration) {
    vp = new VoltageProtocol("vp1");
    ASSERT_THROW(vp->addSteppedStage("step1", -50, 30, 20, -200),
        std::runtime_error);
    
    ASSERT_THROW(vp->addSteppedStage("step1", -50, 30, 20, 0),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Add stepped stage wrong step sign
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addSteppedStageWrongStepSign) {
    vp = new VoltageProtocol("vp1");
    ASSERT_THROW(vp->addSteppedStage("step1", -50, 30, -20, 200),
        std::runtime_error);
    
    ASSERT_THROW(vp->addSteppedStage("step1", 50, -30, 20, 200),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Add more than one stepped stage 
 * Use Case: XX.1 - Extension Xa 
 */
TEST_F(VoltageProtocolTest, addMoreThanOneSteppedStage) {
    vp = new VoltageProtocol("vp1");
    
    vp->addSteppedStage("step1", -50, 30, 20, 200);
    
    ASSERT_THROW(vp->addSteppedStage("step1", 50, -30, -20, 200),
        std::runtime_error);
}

/**
 * Test Case XX.1 - Test getResults success
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, getResultsSuccess) {
    vp = new VoltageProtocol("vp1");
    
    vp->addConstantStage("hold1", -80, 200);
    
    // Note that the 45 for voltage_stop is intentional; 
    // it shouldn't be reached.
    vp->addSteppedStage("step1", -100, 45, 20, 200);
    vp->addConstantStage("hold2", -60, 400);
    
    SerializedVoltageProtocol results = vp->serializeVoltageProtocol();
    
    /*
     * The serialized voltage protocol should look like this:
     *
     * (0, -80), (200, -100), (400, -60), (800, -60)
     * (0, -80), (200, -80) , (400, -60), (800, -60)
     * (0, -80), (200, -60) , (400, -60), (800, -60)
     * (0, -80), (200, -40) , (400, -60), (800, -60)
     * (0, -80), (200, -20) , (400, -60), (800, -60)
     * (0, -80), (200, 0)   , (400, -60), (800, -60)
     * (0, -80), (200, 20)  , (400, -60), (800, -60)
     * (0, -80), (200, 40)  , (400, -60), (800, -60)
     * 
     */
    
    ASSERT_EQ(results[0][0].first, 0);
    ASSERT_EQ(results[0][0].second, -80);
    ASSERT_EQ(results[0][1].first, 200);
    ASSERT_EQ(results[0][1].second, -100);
    ASSERT_EQ(results[0][2].first, 400);
    ASSERT_EQ(results[0][2].second, -60);
    ASSERT_EQ(results[0][3].first, 800);
    ASSERT_EQ(results[0][3].second, -60);
    
    ASSERT_EQ(results[1][0].first, 0);
    ASSERT_EQ(results[1][0].second, -80);
    ASSERT_EQ(results[1][1].first, 200);
    ASSERT_EQ(results[1][1].second, -80);
    ASSERT_EQ(results[1][2].first, 400);
    ASSERT_EQ(results[1][2].second, -60);
    ASSERT_EQ(results[1][3].first, 800);
    ASSERT_EQ(results[1][3].second, -60);
    
    ASSERT_EQ(results[2][0].first, 0);
    ASSERT_EQ(results[2][0].second, -80);
    ASSERT_EQ(results[2][1].first, 200);
    ASSERT_EQ(results[2][1].second, -60);
    ASSERT_EQ(results[2][2].first, 400);
    ASSERT_EQ(results[2][2].second, -60);
    ASSERT_EQ(results[2][3].first, 800);
    ASSERT_EQ(results[2][3].second, -60);
    
    ASSERT_EQ(results[3][0].first, 0);
    ASSERT_EQ(results[3][0].second, -80);
    ASSERT_EQ(results[3][1].first, 200);
    ASSERT_EQ(results[3][1].second, -40);
    ASSERT_EQ(results[3][2].first, 400);
    ASSERT_EQ(results[3][2].second, -60);
    ASSERT_EQ(results[3][3].first, 800);
    ASSERT_EQ(results[3][3].second, -60);
    
    ASSERT_EQ(results[4][0].first, 0);
    ASSERT_EQ(results[4][0].second, -80);
    ASSERT_EQ(results[4][1].first, 200);
    ASSERT_EQ(results[4][1].second, -20);
    ASSERT_EQ(results[4][2].first, 400);
    ASSERT_EQ(results[4][2].second, -60);
    ASSERT_EQ(results[4][3].first, 800);
    ASSERT_EQ(results[4][3].second, -60);
    
    ASSERT_EQ(results[5][0].first, 0);
    ASSERT_EQ(results[5][0].second, -80);
    ASSERT_EQ(results[5][1].first, 200);
    ASSERT_EQ(results[5][1].second, 0);
    ASSERT_EQ(results[5][2].first, 400);
    ASSERT_EQ(results[5][2].second, -60);
    ASSERT_EQ(results[5][3].first, 800);
    ASSERT_EQ(results[5][3].second, -60);
    
    ASSERT_EQ(results[6][0].first, 0);
    ASSERT_EQ(results[6][0].second, -80);
    ASSERT_EQ(results[6][1].first, 200);
    ASSERT_EQ(results[6][1].second, 20);
    ASSERT_EQ(results[6][2].first, 400);
    ASSERT_EQ(results[6][2].second, -60);
    ASSERT_EQ(results[6][3].first, 800);
    ASSERT_EQ(results[6][3].second, -60);
    
    ASSERT_EQ(results[7][0].first, 0);
    ASSERT_EQ(results[7][0].second, -80);
    ASSERT_EQ(results[7][1].first, 200);
    ASSERT_EQ(results[7][1].second, 40);
    ASSERT_EQ(results[7][2].first, 400);
    ASSERT_EQ(results[7][2].second, -60);
    ASSERT_EQ(results[7][3].first, 800);
    ASSERT_EQ(results[7][3].second, -60);
}

/**
 * Test Case XX.1 - Test getResults success with only constant stages
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, getResultsSuccessConstantOnly) {
    vp = new VoltageProtocol("vp1");
    
    vp->addConstantStage("hold1", -80, 200);
    vp->addConstantStage("hold2", -60, 400);
    
    SerializedVoltageProtocol results = vp->serializeVoltageProtocol();
    
    /*
     * The serialized voltage protocol should look like this:
     *
     * (0, -80), (200, -60), (600, -60)
     * 
     */
    
    ASSERT_EQ(results[0][0].first, 0);
    ASSERT_EQ(results[0][0].second, -80);
    ASSERT_EQ(results[0][1].first, 200);
    ASSERT_EQ(results[0][1].second, -60);
    ASSERT_EQ(results[0][2].first, 600);
    ASSERT_EQ(results[0][2].second, -60);
}

/**
 * Test Case XX.1 - Test getResults success with only stepped stage
 * Use Case: XX.1 - Main Success Scenario
 */
TEST_F(VoltageProtocolTest, getResultsSuccessSteppedOnly) {
    vp = new VoltageProtocol("vp1");
    
    // Note that the 45 for voltage_stop is intentional; 
    // it shouldn't be reached.
    vp->addSteppedStage("step1", -20, 25, 20, 200);
    
    SerializedVoltageProtocol results = vp->serializeVoltageProtocol();
    
    /*
     * The serialized voltage protocol should look like this:
     *
     * (0, -20), (200, -20)
     * (0,   0), (200,   0)
     * (0,  20), (200,  20)
     * 
     */
    
    ASSERT_EQ(results[0][0].first, 0);
    ASSERT_EQ(results[0][0].second, -20);
    ASSERT_EQ(results[0][1].first, 200);
    ASSERT_EQ(results[0][1].second, -20);

    ASSERT_EQ(results[1][0].first, 0);
    ASSERT_EQ(results[1][0].second, 0);
    ASSERT_EQ(results[1][1].first, 200);
    ASSERT_EQ(results[1][1].second, 0);
    
    ASSERT_EQ(results[2][0].first, 0);
    ASSERT_EQ(results[2][0].second, 20);
    ASSERT_EQ(results[2][1].first, 200);
    ASSERT_EQ(results[2][1].second, 20);
}






































