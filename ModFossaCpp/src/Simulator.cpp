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

ProtocolIterationResults Simulator::runProtocolIteration(
        ProtocolIteration protocol_iteration,   
        StateOfTheWorld::SharedPointer state_of_the_world, 
        TransitionMatrix::SharedPointer transition_matrix) {
    
    // Set initial voltage and get first 'actual' transition matrix
    state_of_the_world->setVoltage(protocol_iteration[0].second);
    transition_matrix->update(state_of_the_world);
    Matrix T = transition_matrix->get();
    
    int number_of_states = T.n_rows;
    
    // Solve for initial conditions
    std::vector<double> initial_conditions;
    
    // TEMP
    initial_conditions.push_back(1.0);
    for(int i = 0; i < number_of_states -2; ++i ){
        initial_conditions.push_back(1.0);
    }
    // TEMP    
    
    // Create an ODESolver
    ODESolver ode_solver;
    ode_solver.initialize(initial_conditions);
   
    
    ProtocolIterationResults results;
    // Solve each protocol iteration
    // Start initialy at dt, not 0 because we have 
    // already done the initial conditions
    
    
    // The minus 1 is because we have an extra protocol stage which signals
    // that we are done with the protocol_iteration. This last stage is
    // necessary to calculate the stop time of the second to last stage.
    for(int i = 0; i < protocol_iteration.size()-1; ++i) {
               
        double start_time = protocol_iteration[i].first / 1000 + dt;
        double stop_time = protocol_iteration[i+1].first / 1000;
        double voltage = protocol_iteration[i].second;
               
        // This looks awful. It assigns the stop time, which is determined by
        // looking at the start time of the next stage. If we are the last stage,
        // then the stop time is now.
        //double stop_time = (i+1 < protocol_iteration.size()) ? 
        //    (protocol_iteration[i+1].first) : (protocol_iteration[i+1].first);
        //stop_time /= 1000;
        
                      
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

        Matrix mat_results;
        shared_ptr<Matrix>::type t_ptr = std::make_shared<Matrix>(T);
        ode_solver.solve(tspan, t_ptr, mat_results);

        results.push_back(resultsMatrixToVector(mat_results));            
        }
    
    return results;
}
   
std::vector<std::vector<double> > Simulator::resultsMatrixToVector(const Matrix& mat) {
    
    std::cout << mat;
    
    std::vector<std::vector<double> >  results;    
    for(unsigned int i = 0; i < mat.n_rows; ++i){
        
        results.push_back(std::vector<double>());
        double probability = 0.0;
        for(unsigned int j = 0; j < mat.n_cols; ++j) {
            probability += mat(i,j);
            results[i].push_back(mat(i,j));
        }
        results[i].push_back(1.0 - probability);
    }
    
    return results;
}
}
