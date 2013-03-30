/* 
 * File:   Simulator.cpp
 * Author: gareth
 * 
 * Created on March 24, 2013, 12:26 PM
 */

#include <ModFossa/Experiment/Simulator.h>


namespace ModFossa {
Simulator::Simulator() {
}

Simulator::~Simulator() {
}

Vector2d Simulator::runProtocolIteration(
        ProtocolIteration protocol_iteration,   
        StateOfTheWorld::SharedPointer state_of_the_world, 
        TransitionMatrix::SharedPointer transition_matrix) {
    
    // Set initial voltage and get first transition matrix
    state_of_the_world->setVoltage(protocol_iteration[0].second);
    transition_matrix->update(state_of_the_world);
    Matrix T = transition_matrix->get();
       
    int number_of_states = T.n_rows;
    
    /**
     *  Solve for the initial conditions, which are the steady-state
     * probabilities. These can be found by solving the system 
     * S=T/P
     * where P is a column vector of zeros with a one in the final row, and T
     * is our transition matrix.
     * 
     */
    
    // Create column vector
    Matrix P(number_of_states, 1); 
    for(int i = 0; i < number_of_states -1; ++i){
        P(i, 0) = 0.0;
    }
    P(number_of_states - 1, 0) = 1.0;    
   
    /**
     *  Solve for steady-state probabilities which will be our 
     * initial conditions.
     * 
     * @todo Remove the dependency on arma::solve.
     */
    Matrix S = arma::solve(T, P);
    
    // Copy S into an std::vector. Yes, this is lame. Would be better if
    // we didn't actually have to do a deep-copy.
    std::vector<double> initial_conditions;    
    for(int i = 0; i < number_of_states - 1; ++i){
        initial_conditions.push_back(S(i, 0));
    }
    
    
    // Save the initial conditions to our results structure.
    Vector2d results;
    results.push_back(std::vector<double>());
    
    double probability = 0;
    std::vector<double>::const_iterator it;    
    for(it = initial_conditions.begin(); 
            it != initial_conditions.end(); ++it) {
        probability += *it;
        results.back().push_back(*it);
    }
    // Append the probability of the final state, which is calculated using
    // conservation of probabilities.
    results.back().push_back(1.0 - probability);
    
    
    // Create an ODESolver
    ODESolver ode_solver;
    ode_solver.initialize(initial_conditions);   

    // Solve each protocol iteration
    // Start initially at dt, not 0 because we have 
    // already done the initial conditions
    
    
    // The minus 1 is because we have an extra protocol stage which signals
    // that we are done with the protocol_iteration. This last stage is
    // necessary to calculate the stop time of the second to last stage.
    for(unsigned int i = 0; i < protocol_iteration.size()-1; ++i) {
               
        double stop_time = protocol_iteration[i+1].first / 1000;
        double voltage = protocol_iteration[i].second;
        double start_time = protocol_iteration[i].first / 1000;
        
        // If this is our first iteration, start not at time 0, but at dt.
        // Time 0 is the initial conditions, and they have already been saved
        // to the results.
        if(i == 0) {
            start_time += dt;
        } 
                      
        // Create the tspan
        std::vector<double> tspan;
        for(double t = start_time; t <= stop_time; t+=dt){
            tspan.push_back(t);
        }
                    
        // Set state_of_the_world initial voltage
        // We are doing this twice the first time. Fix it.
        state_of_the_world->setVoltage(voltage);
        transition_matrix->update(state_of_the_world);
        Matrix T = transition_matrix->get();

        // The ODESolver returns a Matrix structure.
        Matrix mat_results;
        shared_ptr<Matrix>::type t_ptr = make_shared<Matrix>(T);
        ode_solver.solve(tspan, t_ptr, mat_results);

        // Save the ODE run to our results vector
        resultsMatrixToVector(results, mat_results);         
        }
    
    return results;
}
   
void Simulator::resultsMatrixToVector(
        Vector2d& results, const Matrix& mat) {

    // Copy the results from the solver into our 2-D results vector.
    // The rows of the Matrix are our times. The columns are the state
    // probabilities. The probability of the last state is not calculated by
    // the solver. We calculate it here using conservation of probabilities.
    for(unsigned int i = 0; i < mat.n_rows; ++i){
        
        results.push_back(std::vector<double>());
        double probability = 0.0;
        for(unsigned int j = 0; j < mat.n_cols; ++j) {
            probability += mat(i,j);
            results.back().push_back(mat(i,j));
        }
        results.back().push_back(1.0 - probability);
    }
}
}
