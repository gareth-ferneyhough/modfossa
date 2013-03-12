#include <gtest/gtest.h>
#include <ModelDefinition/State.h>

using namespace ModelDefinition;

/**
 * TestCase for ConstantRateContant. We test the
 * constructor, and the GetRate() method under both
 * normal and un-normal parameters.
 */
class StateTest : public testing::Test {
protected:

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
    State* state;
};

/**
 * Test Case 2.1 - Create State success
 * Use Case: 2.1 - Main Success Scenario
 */
TEST_F(StateTest, createState) {
    state = new State("state1", false);
    ASSERT_TRUE(state->getName() == "state1");
    ASSERT_TRUE(state->getIsConducting() == false);

    delete state;
}

/**
 * Test Case 2.2 - Create State empty name
 * Use Case: 2.1 - Extension 2a
 */
TEST_F(StateTest, createStateEmptyName) {
    ASSERT_THROW(state = new State("", false),
            std::runtime_error);
}




















































