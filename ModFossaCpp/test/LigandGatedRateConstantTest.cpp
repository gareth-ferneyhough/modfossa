#include <cmath>
#include <gtest/gtest.h>
#include <ModelDefinition/LigandGatedRateConstant.h>
#include <ModelDefinition/StateOfTheWorld.h>

using namespace ModelDefinition;

class LigandGatedRateConstantTest : public testing::Test {
protected:

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    LigandGatedRateConstant* rate_constant;
};

/**
 * Test Case 4.1 - Create LigandGatedRateConstant success
 * Use Case: 4.1 - Main Success Scenario
 */
TEST_F(LigandGatedRateConstantTest, createLigandGatedRateConstant) {
    rate_constant = new LigandGatedRateConstant("rc1", "Ca", 2.0);
    ASSERT_TRUE(rate_constant->getName() == "rc1");
    ASSERT_TRUE(rate_constant->getLigandName() == "Ca");
	ASSERT_TRUE(rate_constant->getLigandPower() == 2.0);

    delete rate_constant;
}

/**
 * Test Case 4.2 - Create LigandGatedRateConstant empty name
 * Use Case: 4.1 - Extension 2a
 */
TEST_F(LigandGatedRateConstantTest, createLigandGatedRateConstantEmptyName) {
    ASSERT_THROW(rate_constant = new LigandGatedRateConstant("", "Ca", 2.0),
            std::runtime_error);
}

/**
 * Test Case 4.3 - Create LigandGatedRateConstant empty ligand name
 * Use Case: 4.1 - Extension 2b
 */
TEST_F(LigandGatedRateConstantTest, createLigandGatedRateConstantEmptyLigandName) {
    ASSERT_THROW(rate_constant = new LigandGatedRateConstant("rc1", "", 2.0),
            std::runtime_error);
}

/**
 * Test Case 4.4 - getRate success
 * Use Case: 4.2 - Main Success Scenario
 */
TEST_F(LigandGatedRateConstantTest, getRate) {
    string ligand_name = "Ca";
	double ligand_concentration = 2.0;
	double ligand_power = 3.0;

    shared_ptr<StateOfTheWorld>state_of_the_world(new StateOfTheWorld());
    state_of_the_world->addConcentration(ligand_name, ligand_concentration);

	rate_constant = new LigandGatedRateConstant("rc1", ligand_name, ligand_power);
    double actual = rate_constant->getRate(state_of_the_world);
    double expected = pow(ligand_concentration, ligand_power);

    ASSERT_EQ(expected, actual);

	delete rate_constant;
}

/**
 * Test Case 4.5 - getRate concentration StateOfWorld null
 * Use Case: 4.2 - Extension 2a
 */
TEST_F(LigandGatedRateConstantTest, getRateStateOfWorldNull) {
    shared_ptr<StateOfTheWorld>state_of_the_world = NULL;

	rate_constant = new LigandGatedRateConstant("rc1", "Na", 2.0);
    
	ASSERT_THROW(double actual = rate_constant->getRate(state_of_the_world),
		std::runtime_error);

	delete rate_constant;
}

/**
 * Test Case 4.6 - getRate concentration not declared
 * Use Case: 4.2 - Extension 2b
 */
TEST_F(LigandGatedRateConstantTest, getRateConcentrationNotDeclared) {
    string ligand_name = "Ca";
	double ligand_concentration = 2.0;
	double ligand_power = 3.0;

    shared_ptr<StateOfTheWorld>state_of_the_world(new StateOfTheWorld());
    state_of_the_world->addConcentration(ligand_name, ligand_concentration);

	rate_constant = new LigandGatedRateConstant("rc1", "Na", 2.0);
    
	ASSERT_THROW(double actual = rate_constant->getRate(state_of_the_world),
		std::runtime_error);

	delete rate_constant;
}

