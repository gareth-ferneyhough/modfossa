#include <gtest/gtest.h>
#include <ModelDefinition/MarkovModel.h>
#include <ModelDefinition/ConstantRateConstant.h>
#include <ModelDefinition/TransitionMatrix.h>

using namespace ModelDefinition;

class TransitionMatrixTest : public testing::Test {
protected:

    virtual void SetUp() {
        markov_model = new MarkovModel();

        markov_model->addState(State::SharedPointer(new State("s1", false)));
        markov_model->addState(State::SharedPointer(new State("s2", false)));
        markov_model->addState(State::SharedPointer(new State("s3", true)));

        RateConstantBase::SharedPointer rate1(
                new ConstantRateConstant("rate1", 1.0));

        RateConstantBase::SharedPointer rate2(
                new ConstantRateConstant("rate2", 2.0));

        RateConstantBase::SharedPointer rate3(
                new ConstantRateConstant("rate3", 3.0));

        RateConstantBase::SharedPointer rate4(
                new ConstantRateConstant("rate4", 4.0));

        markov_model->addRateConstant(rate1);
        markov_model->addRateConstant(rate2);
        markov_model->addRateConstant(rate3);
        markov_model->addRateConstant(rate4);

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s1", "s2", "rate1")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s2", "s1", "rate2")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s2", "s3", "rate3")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s3", "s2", "rate4")));

        markov_model->setInitialState("s1");

        state_of_the_world = std::shared_ptr<StateOfTheWorld>(new StateOfTheWorld());
        Validation::ValidationResults results = 
                markov_model->validate(state_of_the_world);
     
        ASSERT_TRUE(results.overall_result == Validation::NO_WARNINGS);

        transition_matrix = new TransitionMatrix(*markov_model);
    }

    virtual void TearDown() {
        delete transition_matrix;
    }

    bool MatricesAreEqual(Matrix a, Matrix b) {
        if ((a.n_rows != b.n_rows) ||
                (a.n_cols != b.n_cols)) {
            return false;
        }

        for (unsigned int i = 0; i < a.n_rows; ++i) {
            for (unsigned int j = 0; j < a.n_cols; ++j) {
                if (a(i, j) != b(i, j)) return false;
            }
        }
        return true;
    }
    
    TransitionMatrix* transition_matrix;
    MarkovModel* markov_model;
    StateOfTheWorld::SharedPointer state_of_the_world;

};

/**
 * Test Case X.1 - Create TransitionMatrix success
 * Use Case: X.X - Main Success Scenario
 */
TEST_F(TransitionMatrixTest, createTransitionMatrix) {
    Matrix expected;
    expected.resize(3, 3);
    expected(0,0) = 1;
    

    transition_matrix->update(state_of_the_world);
    Matrix actual = transition_matrix->get();

    ASSERT_TRUE(MatricesAreEqual(expected, actual));
}



















































