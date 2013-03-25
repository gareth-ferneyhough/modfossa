#include <cmath>
#include <map>
#include <gtest/gtest.h>
#include <ModFossa/ModelDefinition/LigandGatedRateConstant.h>
#include <ModFossa/Common/StateOfTheWorld.h>

using namespace ModFossa;
using std::string;

class LigandGatedRateConstantTest : public testing::Test {
protected:

    virtual void SetUp() {        
        StateOfTheWorld::ConcentrationMap concentrations;
        Concentration::SharedPointer na_concentration(
                new Concentration(ligand_name, ligand_concentration));
        concentrations[ligand_name] = na_concentration;
        
        state_of_the_world = StateOfTheWorld::SharedPointer(
                new StateOfTheWorld(concentrations));
    }

    virtual void TearDown() {

    }
    const string ligand_name = "Na";
    const double ligand_concentration = 2.0;
    LigandGatedRateConstant* rate_constant;
    StateOfTheWorld::SharedPointer state_of_the_world;
};

/**
 * Test Case 4.1 - Create LigandGatedRateConstant success
 * Use Case: 4.1 - Main Success Scenario
 */
TEST_F(LigandGatedRateConstantTest, createLigandGatedRateConstant) {
    rate_constant = new LigandGatedRateConstant("rc1", 2.0, "Ca", 2.0);
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
    ASSERT_THROW(rate_constant = new LigandGatedRateConstant(
            "", 2.0, "Ca", 2.0), std::runtime_error);
}

/**
 * Test Case 4.3 - Create LigandGatedRateConstant empty ligand name
 * Use Case: 4.1 - Extension 2b
 */
TEST_F(LigandGatedRateConstantTest, 
        createLigandGatedRateConstantEmptyLigandName) {
    ASSERT_THROW(rate_constant = new LigandGatedRateConstant(
            "rc1", 2.0, "", 2.0), std::runtime_error);
}

/**
 * Test Case 4.4 - getRate success
 * Use Case: 4.2 - Main Success Scenario
 */
TEST_F(LigandGatedRateConstantTest, getRate) {
    // Create new rate constant dependent.
    double ligand_power = 2.0;
    double k = 2.0;
    rate_constant = new LigandGatedRateConstant("rc1", k, ligand_name, 
        ligand_power);
    
    // getRate() should succeed, because our rate constant depends on a 
    // concentration which has been defined. 
    double actual = rate_constant->getRate(state_of_the_world);
    double expected = k * pow(ligand_concentration, ligand_power);

    ASSERT_EQ(expected, actual);

    delete rate_constant;
}

/**
 * Test Case 4.5 - getRate concentration StateOfWorld null
 * Use Case: 4.2 - Extension 2a
 */
TEST_F(LigandGatedRateConstantTest, getRateStateOfWorldNull) {
    // Set state_of_the_world to NULL
    state_of_the_world = StateOfTheWorld::SharedPointer();

    double ligand_power = 2.0;
    rate_constant = new LigandGatedRateConstant("rc1", 2.0, ligand_name, 
        ligand_power);
    
    // getRate() should throw due to state_of_the_world being null.
    ASSERT_THROW(rate_constant->getRate(state_of_the_world),
            std::runtime_error);

    delete rate_constant;
}

/**
 * Test Case 4.6 - getRate concentration not declared
 * Use Case: 4.2 - Extension 2b
 */
TEST_F(LigandGatedRateConstantTest, getRateConcentrationNotDeclared) {
    // Create a new rate constant dependent on Ca. 
    string ligand_name = "Ca";
    double ligand_concentration = 2.0;

    rate_constant = new LigandGatedRateConstant("rc1", 2.0, ligand_name, 
        ligand_concentration);

    // getRate() should throw, because we do not have a concentration value
    // defined for Ca.
    ASSERT_THROW(rate_constant->getRate(state_of_the_world),
            std::runtime_error);

    delete rate_constant;
}

