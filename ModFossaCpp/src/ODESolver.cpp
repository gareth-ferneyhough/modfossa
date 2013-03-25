/*
 * ODESolver.cpp
 *
 *  Created on: May 30, 2012
 *      Author: gareth
 */

#include <math.h>
#include <ModFossa/Experiment/ODESolver.h>

namespace ModFossa {

ODESolver::ODESolver() :
cvode_mem(0) {
}

ODESolver::~ODESolver() {
}

int ODESolver::initialize(std::vector<double> y0) {
    /* Initialize Sundials CVODE */

    /* Create serial vector for I.C., and results */
    y_size = static_cast<int> (y0.size());
    y_n_vector = N_VNew_Serial(y_size);

    /* Copy y0 into N_VSerial datatype */
    for (unsigned int i = 0; i < y0.size(); ++i) {
        NV_Ith_S(y_n_vector, i) = y0[i];
    }

    /* Set up solver */
    int flag = 0;

    cvode_mem = CVodeCreate(CV_ADAMS, CV_FUNCTIONAL);
    if (cvode_mem == 0) {
        fprintf(stderr, "Error in CVodeCreate: could not allocate\n");
        return -1;
    }

    /* Call CVodeInitto initialize the integrator memory */
    flag = CVodeInit(cvode_mem, (channelProb), 0, y_n_vector);
    if (flag < 0) {
        fprintf(stderr, "Error in CVodeMalloc: %d\n", flag);
        return -1;
    }

    /* Set CVODE tolerances */
    flag = CVodeSStolerances(cvode_mem, reltol, abstol);
    if (flag < 0) {
        fprintf(stderr, "Error in CVodeSStolerances: %d\n", flag);
        return -1;
    }

    /* Set user data so that the rhs function has a pointer to our
     * transition matrix shared pointer 
     */       
    void* user_data = new MatrixSharedPointer*;
    user_data = &transition_matrix;

    flag = CVodeSetUserData(cvode_mem, user_data);
    if (flag < 0) {
        fprintf(stderr, "Error in CVodeSetUserData: %d\n", flag);
        return -1;
    }
    
    return 0;
}

int ODESolver::solve(std::vector<double> tspan, 
        MatrixSharedPointer transition_matrix,
        Matrix& y) {

    this->transition_matrix = transition_matrix;

    // Resize result matrix and copy initial conditions into it.
    int result_rows = tspan.size();
    int result_cols = y_size;
    
    // resize matrix and don't preserve data.
    y.set_size(result_rows, result_cols); 

    /* Solve. In loop, call CVode, save results, and test for error. */
    realtype t_realtype;

    int flag = 0;
    for (unsigned int time_step = 0; time_step < tspan.size(); ++time_step) { 
        
        realtype tout = tspan[time_step];
        realtype tstop = tspan.back();
        // Set the stop time equal to the time at which the voltage changes
        // next. This is to ensure that the solver does not integrate past the
        // stop time, which could mess up the results. 

        if (CVodeSetStopTime(cvode_mem, tstop)) {
            fprintf(stderr, "Error in CVode: %d\n", flag);
            return -1;
        }


        if (CVode(cvode_mem, tout, y_n_vector, 
                &t_realtype, CV_NORMAL) < 0) {
            fprintf(stderr, "Error in CVode: %d\n", flag);
            return -1;
        }

        // Append results to matrix y
        for (int j = 0; j < result_cols; ++j) {
            y(time_step, j) = NV_Ith_S(y_n_vector, j);
        }
    }

    CVodeFree(&cvode_mem);
    N_VDestroy_Serial(y_n_vector); /* Free y vector */

    return 0;
}

/**
 * Static RHS function used by Sundials. Calculates the value of the
 * right hand side of the differential equation at the next timestep, t.
 * This is accomplished by multiplying the transition matrix (less the 
 * last row) with the current state probabilities, y_vec. 
 * 
 * The last row of the transition matrix, T, is removed in order to maintain
 * conservation of probabilities.
 * 
 * ydot = T * y_vec
 * 
 */
int ODESolver::channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
        void *f_data) {

    // Get the transition_matrix pointer from the user-supplied data
    MatrixSharedPointer T = *(MatrixSharedPointer*)f_data;

    // Get the length of y (same as y_dot)
    int y_length = NV_LENGTH_S(y_vec);

    // Get pointer to y_vec and ydot internal data
    double* y_vec_data = N_VGetArrayPointer(y_vec);
    double* ydot_data = N_VGetArrayPointer(ydot);


    // Calculate the sum of state probabilities by adding all elements in
    // y_vec. 
    double total_probability = 0;
    for(int i = 0; i < y_length; ++i) {
        total_probability += y_vec_data[i];
    }

    // Make a new column vector with size y_length + 1 to hold our updated
    // ydot array with all the state probabilities. 
    double state_probabilities[y_length + 1];

    // Copy all y_vec_data into our new vector.
    for(int i = 0; i < y_length; ++ i) {
        state_probabilities[i] = y_vec_data[i];
    }

    // Add the last element so all probabilities sum to 1.
    state_probabilities[y_length] = 1.0 - total_probability;

    // Now multiply the transition matrix with the state probabilities.
    // This will give us our change in probabilities which sundials needs. 

    for(int i = 0; i < y_length; ++i) {
        double sum = 0;
        for(int j = 0; j < y_length + 1; ++j) {
            sum += (*T)(i,j) * state_probabilities[j];
            ydot_data[i] = sum;
        }
    }

    // Thats all.
    return 0;
}
}


