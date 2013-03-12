#include <gtest/gtest.h>
#include <ModelDefinition/ConstantRateConstant.h>
#include <ModelDefinition/StateOfTheWorld.h>

using namespace ModelDefinition;

/**
 * TestCase for ConstantRateContant. We test the
 * constructor, and the GetRate() method under both
 * normal and un-normal parameters.
 */
class ConstantRateConstantTest : public testing::Test {
protected:

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    ConstantRateConstant* rate_constant;
};

/**
 * Test Case 3.1 - Create ConstantRateConstant success
 * Use Case: 3.1 - Main Success Scenario
 */
TEST_F(ConstantRateConstantTest, createConstantRateConstant) {
    rate_constant = new ConstantRateConstant("rc1", 1.1);
    ASSERT_TRUE(rate_constant->getName() == "rc1");
    ASSERT_TRUE(rate_constant->getK() == 1.1);

    delete rate_constant;
}

/**
 * Test Case 3.2 - Create ConstantRateConstant empty name
 * Use Case: 3.1 - Extension 2a
 */
TEST_F(ConstantRateConstantTest, createConstantRateConstantEmptyName) {
    ASSERT_THROW(rate_constant = new ConstantRateConstant("", 0.0),
            std::runtime_error);
}

/**
 * Test Case 3.3 - getRate
 * Use Case: 3.2 - Main Success Scenario
 */
TEST_F(ConstantRateConstantTest, getRate) {
    double k = 1.23;
    rate_constant = new ConstantRateConstant("rc1", k);
    shared_ptr<StateOfTheWorld>state_of_the_world(new StateOfTheWorld());

    double actual = rate_constant->getRate(state_of_the_world);
    double expected = k;
    ASSERT_EQ(expected, actual);

    delete rate_constant;
}


