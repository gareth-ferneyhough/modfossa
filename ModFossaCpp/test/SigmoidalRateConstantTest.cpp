#include <gtest/gtest.h>
#include <ModFossa/ModelDefinition/SigmoidalRateConstant.h>
#include <ModFossa/Common/StateOfTheWorld.h>

using namespace ModFossa;
using std::string;

class SigmoidalRateConstantTest : public testing::Test {
protected:

    virtual void SetUp() {
        rate_constant = NULL;
        
        StateOfTheWorld::ConcentrationMap concentrations;
        Concentration::SharedPointer na_concentration(
                new Concentration(ligand_name, ligand_concentration));
        concentrations[ligand_name] = na_concentration;
        
        state_of_the_world = StateOfTheWorld::SharedPointer(
                new StateOfTheWorld(concentrations));
    }

    virtual void TearDown() {

    }
    
    
    const string ligand_name = "Ca";
    const double ligand_concentration =  3.2;
    SigmoidalRateConstant* rate_constant;
    StateOfTheWorld::SharedPointer state_of_the_world;
};

/**
 * Test default constructor
 */
TEST_F(SigmoidalRateConstantTest, defaultConstructor) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_TRUE(rate_constant != NULL);
    delete rate_constant;
}

/**
 * Test the parameterized constructor for
 * valid input.
 */
TEST_F(SigmoidalRateConstantTest, parameterisedConstructor) {
    rate_constant = new SigmoidalRateConstant("rc1", 1.1, 2.2, 3.3);
    ASSERT_TRUE(rate_constant->getName() == "rc1");
    ASSERT_TRUE(rate_constant->getA() == 1.1);
    ASSERT_TRUE(rate_constant->getVHalf() == 2.2);
    ASSERT_TRUE(rate_constant->getK() == 3.3);


    delete rate_constant;
}

/**
 * Test the parameterized constructor for invalid name parameter.
 */
TEST_F(SigmoidalRateConstantTest, constructorInvalidName) {
    ASSERT_THROW(rate_constant = new SigmoidalRateConstant("", 0, 0, 0),
            std::runtime_error);
}

/**
 * Test the setName() method for invalid name parameter.
 */
TEST_F(SigmoidalRateConstantTest, setInvalidName) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_THROW(rate_constant->setName(""),
            std::runtime_error);
}

/**
 * Test the getRate() method with valid StateOfTheWorld().
 */
TEST_F(SigmoidalRateConstantTest, getRate) {
    double a = 1.1;
    double v_half = 2.2;
    double k = 3.3;
    double voltage = -70;
    rate_constant = new SigmoidalRateConstant("rc1", a, v_half, k);

    state_of_the_world->setVoltage(voltage);

    double error_allowed = 0.000001;
    double actual = rate_constant->getRate(state_of_the_world);
    double expected = 1.0999363635;

    double error = abs(actual - expected);
    ASSERT_LT(error, error_allowed);

    delete rate_constant;
}

/**
 * Test the getRate() method when k has not been set by the user.
 */
TEST_F(SigmoidalRateConstantTest, getRateUnsetK) {
    double a = 1.1;
    double v_half = 2.2;
    rate_constant = new SigmoidalRateConstant();

    rate_constant->setName("rc1");
    rate_constant->setA(a);
    rate_constant->setVHalf(v_half);

    ASSERT_THROW(rate_constant->getRate(state_of_the_world),
            std::runtime_error);

    delete rate_constant;
}

/**
 * Test the getRate() method when state_of_the_world is null
 */
TEST_F(SigmoidalRateConstantTest, getRateStateOfWorldNull) {
    double a = 1.1;
    double v_half = 2.2;
    double k = 3.3;
    rate_constant = new SigmoidalRateConstant("rc1", a, v_half, k);

    ASSERT_THROW(rate_constant->getRate(state_of_the_world),
            std::runtime_error);

    delete rate_constant;
}

TEST_F(SigmoidalRateConstantTest, setName) {
    string name = "rc1";
    rate_constant = new SigmoidalRateConstant();
    rate_constant->setName(name);
    ASSERT_EQ(name, rate_constant->getName());
}

TEST_F(SigmoidalRateConstantTest, setA) {
    double a = 1.1;
    rate_constant = new SigmoidalRateConstant();
    rate_constant->setA(a);
    ASSERT_EQ(a, rate_constant->getA());
}

TEST_F(SigmoidalRateConstantTest, setVHalf) {
    double v_half = 1.1;
    rate_constant = new SigmoidalRateConstant();
    rate_constant->setVHalf(v_half);
    ASSERT_EQ(v_half, rate_constant->getVHalf());
}

TEST_F(SigmoidalRateConstantTest, setK) {
    double k = 1.1;
    rate_constant = new SigmoidalRateConstant();
    rate_constant->setK(k);
    ASSERT_EQ(k, rate_constant->getK());
}

TEST_F(SigmoidalRateConstantTest, getUnsetName) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_THROW(rate_constant->getName(),
            std::runtime_error);
}

TEST_F(SigmoidalRateConstantTest, getUnsetA) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_THROW(rate_constant->getA(),
            std::runtime_error);
}

TEST_F(SigmoidalRateConstantTest, getUnsetVHalf) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_THROW(rate_constant->getVHalf(),
            std::runtime_error);
}

TEST_F(SigmoidalRateConstantTest, getUnsetK) {
    rate_constant = new SigmoidalRateConstant();
    ASSERT_THROW(rate_constant->getK(),
            std::runtime_error);
}
