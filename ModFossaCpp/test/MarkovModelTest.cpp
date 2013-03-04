#include <gtest/gtest.h>
#include <ModelDefinition/State.h>
#include <ModelDefinition/Connection.h>
#include <ModelDefinition/StateOfTheWorld.h>
#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/ConstantRateConstant.h>

#include <algorithm>
#include <memory>

using std::shared_ptr;

using ModelDefinition::MarkovModel;
using ModelDefinition::StateOfTheWorld;
using ModelDefinition::ConstantRateConstant;
using ModelDefinition::State;
using ModelDefinition::Connection;

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
	shared_ptr<const State> state(new State("state1", false));
    markov_model->addState(state);
    delete markov_model;
}

/**
 * Test addState() when state already exists
 */
TEST_F(MarkovModelTest, addStateAlreadyExists) {
    markov_model = new MarkovModel();
	shared_ptr<const State> state1(new State("state1", false));
	shared_ptr<const State> state2(new State("state1", false));

    markov_model->addState(state1);

    ASSERT_THROW(markov_model->addState(state2),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addState() with empty name
 */
TEST_F(MarkovModelTest, addStateEmptyName) {
    markov_model = new MarkovModel();
	State* s1;

    ASSERT_THROW(s1 = new State("", false),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addRateConstant()
 */
TEST_F(MarkovModelTest, addRateConstant) {
    markov_model = new MarkovModel();
    shared_ptr<const ConstantRateConstant> rc (new ConstantRateConstant("rc1", 1.1));
    shared_ptr<const ConstantRateConstant> rc2 (new ConstantRateConstant("rc2", 2.2));

    markov_model->addRateConstant(rc);
    markov_model->addRateConstant(rc2);

    delete markov_model;
}

/**
 * Test addRateConstant() with duplicate name
 */
TEST_F(MarkovModelTest, addDuplicateRateConstant) {
    markov_model = new MarkovModel();
    shared_ptr<const ConstantRateConstant> rc (new ConstantRateConstant("rc1", 1.1));
    shared_ptr<const ConstantRateConstant> rc2 (new ConstantRateConstant("rc1", 2.2));

    markov_model->addRateConstant(rc);
    ASSERT_THROW(markov_model->addRateConstant(rc2),
            std::runtime_error);

    delete markov_model;
}

/**
 * Test addConnection()
 */
TEST_F(MarkovModelTest, addConnection) {
    markov_model = new MarkovModel();
	shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);
    delete markov_model;
}

/**
 * Test add duplicate connection
 */

/**
 * Test validate with initial_state not set
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateInitialStateNotSet) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();

    ValidationResults results = markov_model->validate();

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool initial_state_not_defined_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !initial_state_not_defined_error_exists) {
        if (results.errors[i].first == INITIAL_STATE_NOT_DEFINED) {
            initial_state_not_defined_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(initial_state_not_defined_error_exists);

    delete markov_model;
}

/**
 * Test validate with no connections defined
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateNoConnectionsDefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();

    ValidationResults results = markov_model->validate();

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool no_connections_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !no_connections_error_exists) {
        if (results.errors[i].first == NO_CONNECTIONS) {
            no_connections_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(no_connections_error_exists);

    delete markov_model;
}

/**
 * Test validate with state undefined
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateStateUndefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();
	shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);

    ValidationResults results = markov_model->validate();

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool state_undefined_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !state_undefined_error_exists) {
        if (results.errors[i].first == STATE_NOT_DEFINED) {
            state_undefined_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(state_undefined_error_exists);

    delete markov_model;
}

/**
 * Test validate with rate undefined
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateRateUndefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();
    shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);  

    ValidationResults results = markov_model->validate();

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool rate_constant_undefined_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !rate_constant_undefined_error_exists) {
        if (results.errors[i].first == RATE_CONSTANT_NOT_DEFINED) {
            rate_constant_undefined_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(rate_constant_undefined_error_exists);

    delete markov_model;
}

/**
 * Test validate with valid model
 * Use Case: 1.8 
 */
TEST_F(MarkovModelTest, validateValidModel) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();
    shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);   
    
	shared_ptr<const State> state1(new State("from", false));
	shared_ptr<const State> state2(new State("to", false));

	markov_model->addState(state1);
    markov_model->addState(state2);
    
	markov_model->setInitialState("from");
    
    shared_ptr<const ConstantRateConstant> rc1 (new ConstantRateConstant("rate", 1.1));
    markov_model->addRateConstant(rc1);
    

    ValidationResults results = markov_model->validate();
    ASSERT_TRUE(results.overall_result == NO_WARNINGS);

    delete markov_model;
}