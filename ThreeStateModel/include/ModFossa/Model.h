/*
 * Model.h
 *
 *  Created on: Jun 13, 2012
 *      Author: gareth
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/noncopyable.hpp>

#include <ModFossa/SundialsCpp.h>
#include <ModFossa/State.h>

namespace ModFossa {

class Model: private boost::noncopyable {
public:
    static Model* getInstance();
    void addState(StateName);
    void setConducting(StateName);
    void connect(StateName from, StateName to, double rate);
    void setInitialState(StateName);
    void setIntegrationWindow(std::vector<double> times);
    boost::numeric::ublas::matrix<double> run();

    int numStates() const;
    void setState(const N_Vector& state);
    double inProb(int index);
    double outProb(int index);

    State* getStateByName(StateName name);

private:
    Model();
    ~Model();

    std::vector<State> states;
    std::vector<double> times;
};

// Static RHS function used by Sundials. Calculates the value of the
// right hand side of the differential equation at the next timestep, t.
static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
        void *f_data) {

    Model* model = Model::getInstance();
    // Set current state. Theses are state
    // probabilities of the ion channel model.
    model->setState(y_vec);

    // Set the derivative of each state probability.
    // This is equal to the total probability of transitioning
    // into the state, minus the probability of transitioning out.
    for (int i = 0; i < model->numStates(); ++i) {
        double p_dot_i = model->inProb(i) - model->outProb(i);
        NV_Ith_S(ydot, i) = p_dot_i;
    }

    return 0;
}

} /* namespace ModFossa */
#endif /* MODEL_H_ */
