/*
 * VoltageProtocol.cpp
 *
 *  Created on: Jul 12, 2012
 *      Author: gareth
 */

#include <ModFossa/VoltageProtocol.h>
#include <ModFossa/VoltageEvent.h>

VoltageProtocol::VoltageProtocol() :
        v_hold_start(-1), v_hold_finish(-1), start_time(-1), step_time(-1), finish_time(
                -1), end_time(-1) {
}

void VoltageProtocol::setVstep(std::vector<double> voltages) {
    this->v_step = voltages;
}

void VoltageProtocol::setVholdStart(double v_hold_start) {
    this->v_hold_start = v_hold_start;
}

void VoltageProtocol::setVholdFinish(double v_hold_finish) {
    this->v_hold_finish = v_hold_finish;
}

void VoltageProtocol::setEventTimes(double start, double step, double finish,
        double end) {
    start_time = start;
    step_time = step;
    finish_time = finish;
    end_time = end;
}

void VoltageProtocol::generateVoltageProtocol() {
    std::vector<double>::iterator it;
    for (it = v_step.begin(); it != v_step.end(); ++it) {

        // Create the four voltage events for this value of the voltage protocol step
        VoltageEvent start(start_time, v_hold_start);
        VoltageEvent step(step_time, *it);
        VoltageEvent finish(finish_time, v_hold_finish);
        VoltageEvent end(end_time, 0);

        voltage_clamps.push_back(VoltageClamp(start, step, finish, end));
    }
}

boost::numeric::ublas::matrix<double> VoltageProtocol::getVoltageProtocol() {
    double time_resolution = 0.001; // seconds
    double time_beginning = voltage_clamps[0].v_start.getTimeInstant();
    double time_end = voltage_clamps[0].end.getTimeInstant();

    int num_time_steps = (time_end - time_beginning) / time_resolution;

    boost::numeric::ublas::matrix<double> result;
    result.resize(voltage_clamps.size(), num_time_steps);

    for (int v_index = 0; v_index < voltage_clamps.size(); ++v_index) {
        double time = time_beginning;
        for (int time_index = 0; time_index < num_time_steps; time_index++) {
            result(v_index, time_index) =
                    voltage_clamps[v_index].getVoltageAtTime(time);
            time += time_resolution;
        }
    }

    return result;
}

