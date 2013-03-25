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
    
    double rate1 = 0.1;
    double rate2 = 0.2;
    double rate3 = 0.3;
    double rate4 = 0.4;
    
    shared_ptr<Matrix>::type transition_matrix(new Matrix(3,3));
    (*transition_matrix)(0, 0) = rate1 * -1;
    (*transition_matrix)(0, 1) = rate2;
    (*transition_matrix)(0, 2) = 0;
    
    (*transition_matrix)(1, 0) = rate1;
    (*transition_matrix)(1, 1) = -1*(rate2 + rate3);
    (*transition_matrix)(1, 2) = rate4;
    
    (*transition_matrix)(2, 0) = 0;
    (*transition_matrix)(2, 1) = rate3;
    (*transition_matrix)(2, 2) = rate4 * -1;
    
    std::vector<double> ic;
    ic.push_back(0.1);
    ic.push_back(0.9);
    
    ODESolver solver;
    solver.initialize(ic);
    
    std::vector<double>tspan;
    for(double i = 0.001; i < 0.5; i+=0.001){
        tspan.push_back(i);
    }
    
    Matrix results;
    solver.solve(tspan, transition_matrix, results);
    
    //std::cout << results;
    
    // Not quite sure how to verify this.
}

/**
 * Test Case XX.1 - XX
 * Use Case: XX.1 - XX
 */
TEST_F(ODESolverTest, twoStateModel) {
    double kon = 10;
    double koff = 1;

    
    shared_ptr<Matrix>::type transition_matrix(new Matrix(2,2));
    (*transition_matrix)(0, 0) = kon * -1;
    (*transition_matrix)(0, 1) = koff;
    
    (*transition_matrix)(1, 0) = kon;
    (*transition_matrix)(1, 1) = koff * -1;

    
    std::vector<double> ic;
    ic.push_back(1);
    
    ODESolver solver;
    solver.initialize(ic);
    
    std::vector<double>tspan;
    for(double i = 0.001; i < 0.5; i+=0.001){
        tspan.push_back(i);
    }
    
    Matrix results;
    solver.solve(tspan, transition_matrix, results);
    //std::cout << "tmatrix1 " << *transition_matrix;
    std::cout << results;
    
    // Not quite sure how to verify this.
}
