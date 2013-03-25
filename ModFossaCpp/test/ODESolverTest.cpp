#include <string>
#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include <ModFossa/Experiment/ODESolver.h>

using namespace ModFossa;
using std::string;

class ODESolverTest : public testing::Test {
protected:

    virtual void SetUp() {  
    }

    virtual void TearDown() {
    }
};

/**
 * Test Case XX.1 - XX
 * Use Case: XX.1 - XX
 */
TEST_F(ODESolverTest, createSuccess) {
    
    shared_ptr<Matrix>::type transition_matrix(new Matrix(3,3));
    (*transition_matrix)(0, 0) = 1;
    (*transition_matrix)(0, 1) = 2;
    (*transition_matrix)(0, 2) = 3;
    (*transition_matrix)(1, 0) = 4;
    (*transition_matrix)(1, 1) = 5;
    (*transition_matrix)(1, 2) = 6;
    (*transition_matrix)(2, 0) = 7;
    (*transition_matrix)(2, 1) = 8;
    (*transition_matrix)(2, 2) = 9;
    
    std::vector<double> ic;
    ic.push_back(0.1);
    ic.push_back(0.9);
    
    ODESolver solver;
    solver.initialize(ic);
    
    Matrix results;
    
    solver.solve(10, transition_matrix, results);
    
    std::cout << results;
}
