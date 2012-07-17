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
#include <ModFossa/RateConstant.h>

namespace ModFossa {

class Model: private boost::noncopyable {
public:
    static Model* getInstance();
    void addState(StateName);
    void setConducting(StateName);
    void connect(StateName from, StateName to, std::string rate_constant);
    void setInitialState(StateName);
    void setIntegrationWindow(std::vector<double> times);
    void setVstep(std::vector<double> voltages);
    void setVholdStart(double);
    void setVholdFinish(double);
    void setEventTimes(double start, double step, double finish, double end);

    void addRateConstant(std::string type, double a, double v_half, double k, std::string name);
    //void addRateConstant(std::string type, double k, std::string name);

    boost::numeric::ublas::matrix<double> run();
    boost::numeric::ublas::matrix<double> getVoltageProtocol();

    int numStates() const;
    void setState(const N_Vector& state);
    double inProb(int index);
    double outProb(int index);

    State* getStateByName(StateName name);
    RateConstant* getRateConstantByName(std::string name);

private:
    Model();
    ~Model();

    std::vector<RateConstant> rate_constants;
    std::vector<State> states;
    std::vector<double> times;

    VoltageProtocol voltage_protocol;

    double membrane_voltage;
};

static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot, void *f_data);

} /* namespace ModFossa */
#endif /* MODEL_H_ */
