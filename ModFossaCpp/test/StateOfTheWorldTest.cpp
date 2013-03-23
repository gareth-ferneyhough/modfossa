#include <gtest/gtest.h>
#include <ModFossa/Common/StateOfTheWorld.h>

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
        Concentration::SharedPointer c1(new Concentration(ca_name, ca_value));
        Concentration::SharedPointer c2(new Concentration(na_name, na_value));
        Concentration::SharedPointer c3(new Concentration(k_name, k_value));
        
        StateOfTheWorld::ConcentrationMap map;
        map[ca_name] = c1;
        map[na_name] = c2;
        map[k_name] = c3;
        
        state_of_the_world = StateOfTheWorld::SharedPointer(
                new StateOfTheWorld(map));

    }

    virtual void TearDown() {

    }

    const string ca_name = "Ca";
    const string na_name = "Na";
    const string k_name = "K";
    
    const double ca_value = 1.1;
    const double na_value = 2.2;
    const double k_value = 3.3;
    
    StateOfTheWorld::SharedPointer state_of_the_world;
};

/**
 * Test getConcentration() with ligand name that exists.
 */
TEST_F(StateOfTheWorldTest, getConcentration) {
    ASSERT_TRUE(state_of_the_world->getConcentration(ca_name) == ca_value);
    ASSERT_TRUE(state_of_the_world->getConcentration(na_name) == na_value);
    ASSERT_TRUE(state_of_the_world->getConcentration(k_name) == k_value);
}

/**
 * Test getConcentration() with ligand name that does not exist.
 */
TEST_F(StateOfTheWorldTest, getUndeclaredConcentration) {
    ASSERT_THROW(state_of_the_world->getConcentration("Cl"),
            std::runtime_error);
}
