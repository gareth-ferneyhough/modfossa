#include <gtest/gtest.h>
#include <ModelDefinition/StateOfTheWorld.h>
#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/ConstantRateConstant.h>

#include <algorithm>

using ModelDefinition::MarkovModel;
using ModelDefinition::StateOfTheWorld;
using ModelDefinition::ConstantRateConstant;

class MarkovModelTest : public testing::Test {
protected:

    virtual void SetUp() {
        state_of_the_world = NULL;
        markov_model = NULL;
    }

    virtual void TearDown() {

    }

    MarkovModel* markov_model;
    StateOfTheWorld* state_of_the_world;
};

/**
 * Test default constructor
 */
TEST_F(MarkovModelTest, defaultConstructor) {
    markov_model = new MarkovModel();
    ASSERT_TRUE(markov_model != NULL);
    delete markov_model;
}

/**
 * Test addState()
 */
TEST_F(MarkovModelTest, addState) {
    markov_model = new MarkovModel();
    markov_model->addState("state1", false);
    delete markov_model;
}

/**
 * Test addState() when state already exists
 */
TEST_F(MarkovModelTest, addStateAlreadyExists) {
    markov_model = new MarkovModel();
    markov_model->addState("state1", false);

    ASSERT_THROW(markov_model->addState("state1", false),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addState() with empty name
 */
TEST_F(MarkovModelTest, addStateEmptyName) {
    markov_model = new MarkovModel();

    ASSERT_THROW(markov_model->addState("", false),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addRateConstant()
 */
TEST_F(MarkovModelTest, addRateConstant) {
    markov_model = new MarkovModel();
    ConstantRateConstant * rc = new ConstantRateConstant("rc1", 1.1);
    ConstantRateConstant * rc2 = new ConstantRateConstant("rc2", 2.2);

    markov_model->addRateConstant(*rc);
    markov_model->addRateConstant(*rc2);

    delete markov_model;
}

/**
 * Test addRateConstant() with duplicate name
 */
TEST_F(MarkovModelTest, addDuplicateRateConstant) {
    markov_model = new MarkovModel();
    ConstantRateConstant * rc = new ConstantRateConstant("rc1", 1.1);
    ConstantRateConstant * rc2 = new ConstantRateConstant("rc1", 2.2);

    markov_model->addRateConstant(*rc);
    ASSERT_THROW(markov_model->addRateConstant(*rc2),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addConnection()
 */
TEST_F(MarkovModelTest, addConnection) {
    markov_model = new MarkovModel();
    markov_model->addConnection("start", "end", "rc1");
    delete markov_model;
}

/**
 * Test validate with initial_state not set
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateInitialStateNotSet) {
    using namespace ModelDefinition::Validation;
    
    markov_model = new MarkovModel();
    
    ValidationResults results = markov_model->validate();
    
    ASSERT_TRUE(results.overall_result == ERRORS);
            
    typedef std::pair<ErrorType, string> pair_type;
        std::find_if(results.errors.begin(), results.errors.end(), 
        [](pair_type const& pair)
        { return pair.first == INITIAL_STATE_NOT_DEFINED; });
    
    delete markov_model;
}