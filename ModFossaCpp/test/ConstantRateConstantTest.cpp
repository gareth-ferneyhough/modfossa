#include <gtest/gtest.h>
#include <ConstantRateConstant.h>


/**
 * TestCase for ConstantRateContant. We test the
 * constructor, and the GetRate() method under both
 * normal and unnormal parameters.
 */
class ConstantRateConstantTest : public testing::Test {
protected:
  virtual void SetUp() {

  }

  virtual void TearDown() {

  }

  ConstantRateConstant* rateConstant;
  //StateOfTheWorld* stateOfTheWorld;  
};
  

/**
 * Test default constructor
 */
TEST_F(ConstantRateConstantTest, DefaultConstructor) {
  rateConstant = new ConstantRateConstant();
  ASSERT_TRUE(rateConstant != NULL);
  delete rateConstant;
}

/**
 * Test the parameterized constructor for
 * valid input.
 */
TEST_F(ConstantRateConstantTest, ParameterisedConstructor) {
  rateConstant = new ConstantRateConstant("rc1", 0.0);
  ASSERT_TRUE(rateConstant != NULL);  
  delete rateConstant;
}

/**
 * Test the parameterized constructor for invlaid name parameters.
 */
TEST_F(ConstantRateConstantTest, ConstructorInvalidName) {
  rateConstant = new ConstantRateConstant("", 0.0);
  //ASSERT_TRUE(rateConstant != null); need to check exception here
  delete rateConstant;
}

/**
 * Test the GetRate() method with valid StateOfTheWorld().
 */
TEST_F(ConstantRateConstantTest, GetRate) {
  rateConstant = new ConstantRateConstant("rc1", 0.0);
  //stateOfTheWorld = new StateOfTheWorld();
  //  stateOfTheWorld.AddConcentration("Ca", 3.2);

  double actual = 0;//rateConstant.GetRate(stateOfTheWorld);
  double expected = 1.23;
  ASSERT_EQ(expected, actual);

  delete rateConstant;
  //  delete stateOfTheWorld;
}


