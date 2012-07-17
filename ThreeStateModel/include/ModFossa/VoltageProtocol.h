/*
 * VoltageProtocol.h
 *
 *  Created on: Jul 12, 2012
 *      Author: gareth
 */

#ifndef VOLTAGEPROTOCOL_H_
#define VOLTAGEPROTOCOL_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <ModFossa/VoltageClamp.h>

class VoltageProtocol {
public:
    VoltageProtocol();
    void setVstep(std::vector<double> voltages);
    void setVholdStart(double);
    void setVholdFinish(double);
    void setEventTimes(double start, double step, double finish, double end);

    void generateVoltageProtocol();
    std::vector<VoltageClamp> voltage_clamps;

    boost::numeric::ublas::matrix<double> getVoltageProtocol();

private:

    std::vector<double> v_step;
    double v_hold_start;
    double v_hold_finish;

    double start_time;
    double step_time;
    double finish_time;
    double end_time;

};

#endif /* VOLTAGEPROTOCOL_H_ */
