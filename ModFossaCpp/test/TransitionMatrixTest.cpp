#include <gtest/gtest.h>
#include <ModFossa/ModelDefinition/MarkovModel.h>
#include <ModFossa/ModelDefinition/ConstantRateConstant.h>
#include <ModFossa/ModelDefinition/TransitionMatrix.h>

using namespace ModFossa;
using std::string;

class TransitionMatrixTest : public testing::Test {
protected:

    virtual void SetUp() {
        /**
         * Create a valid MarkovModel with three states.
         * All rate constants are constant.   
         */
        
        markov_model = new MarkovModel();

        markov_model->addState(State::SharedPointer(new State("s1", false)));
        markov_model->addState(State::SharedPointer(new State("s2", false)));
        markov_model->addState(State::SharedPointer(new State("s3", true)));

        RateConstantBase::SharedPointer rate1(
                new ConstantRateConstant("k1", 1.0));

        RateConstantBase::SharedPointer rate2(
                new ConstantRateConstant("k2", 2.0));

        RateConstantBase::SharedPointer rate3(
                new ConstantRateConstant("k3", 3.0));

        RateConstantBase::SharedPointer rate4(
                new ConstantRateConstant("k4", 4.0));

        markov_model->addRateConstant(rate1);
        markov_model->addRateConstant(rate2);
        markov_model->addRateConstant(rate3);
        markov_model->addRateConstant(rate4);

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s1", "s2", "k1")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s2", "s1", "k2")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s2", "s3", "k3")));

        markov_model->addConnection(Connection::SharedPointer(
                new Connection("s3", "s2", "k4")));

        markov_model->setInitialState("s1");

        StateOfTheWorld::ConcentrationMap concentrations;
        state_of_the_world = StateOfTheWorld::SharedPointer(
                new StateOfTheWorld(concentrations));
        
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
    
    /**
     * The resulting transition matrix from our MarkovModel
     * should look like this:
     * 
     *        Ps1    Ps2     Ps3
     * dPs1 | -k1     k2        |          
     * dPs2 |  k1    -k2-k3  k4 |
     * dPs3 |         k3    -k4 |
     * 
     */
    
    Matrix expected;
    expected.resize(3, 3);
    
    expected(0,0) = -1;
    expected(0,1) = 2;
    expected(0,2) = 0;
    
    expected(1,0) = 1;
    expected(1,1) = -2-3;
    expected(1,2) = 4;
    
    expected(2,0) = 0;
    expected(2,1) = 3;
    expected(2,2) = -4;
    

    transition_matrix->update(state_of_the_world);
    Matrix actual = transition_matrix->get();

    ASSERT_TRUE(MatricesAreEqual(expected, actual));
}



















































