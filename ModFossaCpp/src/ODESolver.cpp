/*
 * ODESolver.cpp
 *
 *  Created on: May 30, 2012
 *      Author: gareth
 */

#include <math.h>
#include <ModFossa/Experiment/ODESolver.h>

namespace ModFossa {

    //int channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
      //      void *f_data);

    ODESolver::ODESolver() :
    reltol(1e-6),
    abstol(1e-8),
    cvode_mem(0),
    current_time(1) {
    odefun = channelProb;
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
        flag = CVodeInit(cvode_mem, (odefun), 0, y_n_vector);
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
        
        /* Set user data */
//        void* user_data = new int*;
//        user_data = &y_size;
        //std::cout << *(int*)user_data << std::endl;
        
        void* user_data = new MatrixSharedPointer*;
        user_data = &transition_matrix;

        flag = CVodeSetUserData(cvode_mem, user_data);
        if (flag < 0) {
            fprintf(stderr, "Error in CVodeSetUserData: %d\n", flag);
            return -1;
        }


        return 0;
    }

    int ODESolver::solve(int stop_time, MatrixSharedPointer transition_matrix,
            Matrix& y) {

        this->transition_matrix = transition_matrix;

        // Resize result matrix and copy initial conditions into it.
        int result_rows = stop_time - current_time + 1;
        int result_cols = y_size;
        y.set_size(result_rows, result_cols); // resize matrix and don't preserve data

        /* Solve. In loop, call CVode, save results, and test for error */
        realtype t_realtype;

        int flag = 0;
        int results_index = 0;
        while (current_time <= stop_time) {

            // Set the stop time equal to the time at which the voltage changes
            // next. This is to ensure that the solver does not integrate past the
            // stop time, which could mess up the results. 

            if (CVodeSetStopTime(cvode_mem, stop_time)) {
                fprintf(stderr, "Error in CVode: %d\n", flag);
                return -1;
            }


            if (CVode(cvode_mem, current_time, y_n_vector, &t_realtype, CV_NORMAL) < 0) {
                fprintf(stderr, "Error in CVode: %d\n", flag);
                return -1;
            }

            // Append results to matrix y
            for (int j = 0; j < result_cols; ++j) {
                y(results_index, j) = NV_Ith_S(y_n_vector, j);
            }
            current_time++;
            results_index++;
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
            for(int j = 0; j < y_length + 1; ++j) {
                double sum = 0;
                sum += (*T)(i,j) * state_probabilities[j];
                ydot_data[i] = sum;
            }
        }

        // Thats all.
        return 0;
    }
}


