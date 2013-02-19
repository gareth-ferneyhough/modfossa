#include <gtest/gtest.h>
#include <ConstantRateConstant.h>
#include <StateOfTheWorld.h>

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
    StateOfTheWorld* state_of_the_world;
};

/**
 * Test default constructor
 */
TEST_F(ConstantRateConstantTest, defaultConstructor) {
    rate_constant = new ConstantRateConstant();
    ASSERT_TRUE(rate_constant != NULL);
    delete rate_constant;
}

/**
 * Test the parameterized constructor for
 * valid input.
 */
TEST_F(ConstantRateConstantTest, parameterisedConstructor) {
    rate_constant = new ConstantRateConstant("rc1", 1.1);
    ASSERT_TRUE(rate_constant->getName() == "rc1");
    ASSERT_TRUE(rate_constant->getK() == 1.1);

    delete rate_constant;
}

/**
 * Test the parameterized constructor for invalid name parameter.
 */
TEST_F(ConstantRateConstantTest, constructorInvalidName) {
    ASSERT_THROW(rate_constant = new ConstantRateConstant("", 0.0),
            std::runtime_error);
}

/**
 * Test the setName() method for invalid name parameter.
 */
TEST_F(ConstantRateConstantTest, setInvalidName) {
    rate_constant = new ConstantRateConstant();
    ASSERT_THROW(rate_constant->setName(""),
            std::runtime_error);
}

/**
 * Test the getRate() method with valid StateOfTheWorld().
 */
TEST_F(ConstantRateConstantTest, getRate) {
    double k = 1.23;
    rate_constant = new ConstantRateConstant("rc1", k);
    state_of_the_world = new StateOfTheWorld();
    state_of_the_world->addConcentration("Ca", 3.2);

    double actual = rate_constant->getRate(state_of_the_world);
    double expected = k;
    ASSERT_EQ(expected, actual);

    delete rate_constant;
    delete state_of_the_world;
}


