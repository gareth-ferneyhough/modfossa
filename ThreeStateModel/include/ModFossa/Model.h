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
#include <ModFossa/VoltageProtocol.h>

namespace ModFossa {

class Model: private boost::noncopyable {
public:
    static Model* getInstance();
    void addState(StateName);
    void setConducting(StateName);
    void connect(StateName from, StateName to, double rate);
    void setInitialState(StateName);
    void setIntegrationWindow(std::vector<double> times);
    void setVstep(std::vector<double> voltages);
    void setVholdStart(double);
    void setVholdFinish(double);
    void setEventTimes(double start, double step, double finish, double end);

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

    VoltageProtocol voltage_protocol;
};

static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot, void *f_data);

} /* namespace ModFossa */
#endif /* MODEL_H_ */
