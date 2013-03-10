#include <gtest/gtest.h>
#include <ModelDefinition/State.h>
#include <ModelDefinition/Connection.h>
#include <ModelDefinition/StateOfTheWorld.h>
#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/ConstantRateConstant.h>
#include <ModelDefinition/LigandGatedRateConstant.h>

#include <algorithm>
#include <memory>

using std::shared_ptr;

using ModelDefinition::MarkovModel;
using ModelDefinition::StateOfTheWorld;
using ModelDefinition::ConstantRateConstant;
using ModelDefinition::LigandGatedRateConstant;
using ModelDefinition::State;
using ModelDefinition::Connection;

class MarkovModelTest : public testing::Test {
protected:

    virtual void SetUp() {
        markov_model = NULL;
    }

    virtual void TearDown() {

    }

    MarkovModel* markov_model;
};

/**
 * Test Case 1.1 - addRateConstant success
 * Use Case: 1.1 - Main Success Scenario
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
 * Test Case 1.2 - addRateConstant duplicate name
 * Use Case: 1.1 - Extension 2a
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
 * Test Case 1.3 - addState success
 * Use Case: 1.2 - Main Success Scenario
 */
TEST_F(MarkovModelTest, addState) {
    markov_model = new MarkovModel();
	shared_ptr<const State> state(new State("state1", false));
    markov_model->addState(state);
    delete markov_model;
}

/**
 * Test Case 1.4 - addState duplicate name
 * Use Case: 1.2 - Extension 2a
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
 * Test Case 1.5 - addConnection success
 * Use Case: 1.3 - Main Success Scenario
 */
TEST_F(MarkovModelTest, addConnection) {
    markov_model = new MarkovModel();
	shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);
    delete markov_model;
}

/**
 * Test Case 1.6 - addState duplicate connection
 * Use Case: 1.3 - Extension 2a
 */
TEST_F(MarkovModelTest, addDuplicateConnection) {
    markov_model = new MarkovModel();
	shared_ptr<const Connection> connection1(new Connection("from", "to", "rate"));
	shared_ptr<const Connection> connection2(new Connection("from", "to", "rate2"));
    
	markov_model->addConnection(connection1);
	ASSERT_THROW(markov_model->addConnection(connection1),
        std::runtime_error);

    delete markov_model;
}

/**
 * Test Case 1.7 - setInitialState success
 * Use Case: 1.4 - Main Success Scenario
 */
TEST_F(MarkovModelTest, setInitialState) {
    markov_model = new MarkovModel();
	markov_model->setInitialState("s1");
    delete markov_model;
}

/**
 * Test Case 1.8 - setInitialState already set
 * Use Case: 1.4 - Extension 2a
 */
TEST_F(MarkovModelTest, setInitialStateDuplicate) {
    markov_model = new MarkovModel();
	markov_model->setInitialState("s1");

	ASSERT_THROW(markov_model->setInitialState("s1"),
		std::runtime_error);
    delete markov_model;
}

/**
 * Test Case 1.9 - validate success
 * Use Case: 1.5 - Main Success Scenarios
 */
TEST_F(MarkovModelTest, validateSuccess) {
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
    
	std::shared_ptr<StateOfTheWorld> state_of_the_world(new StateOfTheWorld());
    ValidationResults results = markov_model->validate(state_of_the_world);
    ASSERT_TRUE(results.overall_result == NO_WARNINGS);

    delete markov_model;
}

/**
 * Test Case 1.10 - validate success with LigandGatedRateConstant
 * Use Case: 1.5 - Main Success Scenario
 */
TEST_F(MarkovModelTest, validateSuccessWithLigandGated) {
    using namespace ModelDefinition::Validation;

    string ligand_name = "Ca";
	double ligand_power = 2.0;
	double ligand_concentration = 3.0;

	std::shared_ptr<LigandGatedRateConstant> rate1(new LigandGatedRateConstant(
		"rate1", ligand_name, ligand_power)); 
	
	std::shared_ptr<State> state_1(new State("state1", true));
	std::shared_ptr<State> state_2(new State("state2", false));
	std::shared_ptr<Connection> connection(new Connection("state1", "state2", "rate1"));

	std::shared_ptr<StateOfTheWorld> state_of_the_world(new StateOfTheWorld());
	state_of_the_world->addConcentration(ligand_name, ligand_concentration);
	
	markov_model = new MarkovModel();
	markov_model->addState(state_1);
	markov_model->addState(state_2);
	markov_model->addRateConstant(rate1);
	markov_model->addConnection(connection);
	markov_model->setInitialState("state1");

    ValidationResults results = markov_model->validate(state_of_the_world);
	ASSERT_TRUE(results.overall_result == NO_WARNINGS);

    delete markov_model;
}

/**
 * Test Case 1.11 - validate no connections defined
 * Use Case: 1.5 - Extension 2a
 */
TEST_F(MarkovModelTest, validateNoConnectionsDefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();

    ValidationResults results = markov_model->validate(NULL);

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
 * Test Case 1.12 - validate State undefined
 * Use Case: 1.5 - Extension 3a
 */
TEST_F(MarkovModelTest, validateStateUndefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();
	shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);

    ValidationResults results = markov_model->validate(NULL);

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
 * Test Case 1.13 - validate RateConstant undefined
 * Use Case: 1.5 - Extension 4a
 */
TEST_F(MarkovModelTest, validateRateUndefined) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();
    shared_ptr<const Connection> connection(new Connection("from", "to", "rate"));
    markov_model->addConnection(connection);  

    ValidationResults results = markov_model->validate(NULL);

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
 * Test Case 1.14 - validate initial state not set
 * Use Case: 1.5 - Extension 5a
 */
TEST_F(MarkovModelTest, validateInitialStateNotSet) {
    using namespace ModelDefinition::Validation;

    markov_model = new MarkovModel();

    ValidationResults results = markov_model->validate(NULL);

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
 * Test Case 1.15 - validate StateOfTheWorld null
 * Use Case: 1.5 - Extension 6a
 */
TEST_F(MarkovModelTest, validateStateOfTheWorldNull) {
    using namespace ModelDefinition::Validation;

    string ligand_name = "Ca";
	double ligand_power = 2.0;
	double ligand_concentration = 3.0;

	std::shared_ptr<LigandGatedRateConstant> rate1(new LigandGatedRateConstant(
		"rate1", "Na", 4.0)); 
	
	std::shared_ptr<State> state_1(new State("state1", true));
	std::shared_ptr<State> state_2(new State("state2", false));
	std::shared_ptr<Connection> connection(new Connection("state1", "state2", "rate1"));

	std::shared_ptr<StateOfTheWorld> state_of_the_world = NULL;

	
	markov_model = new MarkovModel();
	markov_model->addState(state_1);
	markov_model->addState(state_2);
	markov_model->addRateConstant(rate1);
	markov_model->addConnection(connection);
	markov_model->setInitialState("state1");

    ValidationResults results = markov_model->validate(state_of_the_world);

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool state_of_world_null_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !state_of_world_null_error_exists) {
        if (results.errors[i].first == STATE_OF_THE_WORLD_IS_NULL) {
            state_of_world_null_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(state_of_world_null_error_exists);

    delete markov_model;
}

/**
 * Test Case 1.16 - validate concentration not defined
 * Use Case: 1.5 - Extension 6b
 */
TEST_F(MarkovModelTest, validateConcentrationNotDefined) {
    using namespace ModelDefinition::Validation;

    string ligand_name = "Ca";
	double ligand_power = 2.0;
	double ligand_concentration = 3.0;

	std::shared_ptr<LigandGatedRateConstant> rate1(new LigandGatedRateConstant(
		"rate1", "Na", 4.0)); 
	
	std::shared_ptr<State> state_1(new State("state1", true));
	std::shared_ptr<State> state_2(new State("state2", false));
	std::shared_ptr<Connection> connection(new Connection("state1", "state2", "rate1"));

	std::shared_ptr<StateOfTheWorld> state_of_the_world(new StateOfTheWorld());
	state_of_the_world->addConcentration(ligand_name, ligand_concentration);
	
	markov_model = new MarkovModel();
	markov_model->addState(state_1);
	markov_model->addState(state_2);
	markov_model->addRateConstant(rate1);
	markov_model->addConnection(connection);
	markov_model->setInitialState("state1");

    ValidationResults results = markov_model->validate(state_of_the_world);

    ASSERT_TRUE(results.overall_result == ERRORS);

    bool concentration_not_defined_error_exists = false;
    int i = 0;
    while (i < results.errors.size() && 
            !concentration_not_defined_error_exists) {
        if (results.errors[i].first == LIGAND_NOT_DEFINED) {
            concentration_not_defined_error_exists = true;
        }
        ++i;
    }

    ASSERT_TRUE(concentration_not_defined_error_exists);

    delete markov_model;
}
