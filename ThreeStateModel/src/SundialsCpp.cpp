/*
 * SundialsCpp.cpp
 *
 *  Created on: May 30, 2012
 *      Author: gareth
 */

#include <math.h>
#include <ModFossa/SundialsCpp.h>

SundialsCpp::SundialsCpp() :
        reltol(1e-6), abstol(1e-8), cvode_mem(0) {
}

SundialsCpp::~SundialsCpp() {
}

int SundialsCpp::solve(CVRhsFn odefun, std::vector<double> tspan,
        std::vector<double> y0, matrix<double>& y) {
    /* Initialize Sundials CVODE */

    /*	Create serial vector for I.C., and results */
    N_Vector y_n_vector = N_VNew_Serial(static_cast<int>(y0.size()));

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
    flag = CVodeInit(cvode_mem, (odefun), tspan[0], y_n_vector);
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

    // Resize result matrix and copy initial conditions into it.
    size_t result_rows = tspan.size();
    size_t result_cols = y0.size();
    y.resize(result_rows, result_cols, false); // resize matrix and don't preserve data

    // Copy i.c.
    for (unsigned int i = 0; i < result_cols; ++i) {
        y(0, i) = y0[i];
    }

    /* Solve. In loop, call CVode, save results, and test for error */
    realtype t_realtype;
    for (unsigned int time_step = 1; time_step < tspan.size(); ++time_step) { // Note: integration must start at tspan[1] (tspan[0] is i.c.)
        realtype tout = tspan[time_step];
        if (CVode(cvode_mem, tout, y_n_vector, &t_realtype, CV_NORMAL) < 0) {
            fprintf(stderr, "Error in CVode: %d\n", flag);
            return -1;
        }

        // Append results to matrix y
        for (unsigned int j = 0; j < result_cols; ++j) {
            y(time_step, j) = NV_Ith_S(y_n_vector, j);
        }
    }

    CVodeFree(&cvode_mem);
    N_VDestroy_Serial(y_n_vector); /* Free y vector */

    return 0;
}

