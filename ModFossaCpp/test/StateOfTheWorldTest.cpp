#include <gtest/gtest.h>
#include <ModFossa/ModelDefinition/StateOfTheWorld.h>

using namespace ModFossa;
using std::string;

/**
 * TestCase for ConstantRateContant. We test the
 * constructor, and the getRate() method under both
 * normal and unnormal parameters.
 */
class StateOfTheWorldTest : public testing::Test {
protected:

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

    StateOfTheWorld* state_of_the_world;
};

/**
 * Test default constructor
 */
TEST_F(StateOfTheWorldTest, defaultConstructor) {
    state_of_the_world = new StateOfTheWorld();
    ASSERT_TRUE(state_of_the_world != NULL);
    delete state_of_the_world;
}

/**
 * Test getConcentration() with ligand name that exists.
 */
TEST_F(StateOfTheWorldTest, getConcentration) {
    state_of_the_world = new StateOfTheWorld();

    state_of_the_world->addConcentration("Ca", 1.11);
    state_of_the_world->addConcentration("Na", 2.22);
    state_of_the_world->addConcentration("K", 3.33);

    ASSERT_TRUE(state_of_the_world->getConcentration("Ca") == 1.11);
    ASSERT_TRUE(state_of_the_world->getConcentration("Na") == 2.22);
    ASSERT_TRUE(state_of_the_world->getConcentration("K") == 3.33);
}

/**
 * Test getConcentration() with ligand name that does not exist.
 */
TEST_F(StateOfTheWorldTest, getUndeclaredConcentration) {
    state_of_the_world = new StateOfTheWorld();

    state_of_the_world->addConcentration("Ca", 1.1);


    ASSERT_THROW(state_of_the_world->getConcentration("Na"),
            std::runtime_error);
}

/**
 * Test getConcentration() when the map of Concentrations has not been 
 * initialized.
 */
TEST_F(StateOfTheWorldTest, concentrationsNotSet) {
    state_of_the_world = new StateOfTheWorld();
    ASSERT_THROW(state_of_the_world->getConcentration("Na"),
            std::runtime_error);
}

TEST_F(StateOfTheWorldTest, addConcentrationNoMap) {
    state_of_the_world = new StateOfTheWorld();
    state_of_the_world->addConcentration("Na", 1.23);

    ASSERT_TRUE(state_of_the_world->getConcentration("Na") == 1.23);
}