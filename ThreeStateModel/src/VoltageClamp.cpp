/*
 * VoltageClamp.cpp
 *
 *  Created on: Jul 12, 2012
 *      Author: gareth
 */

#include <ModFossa/VoltageClamp.h>

VoltageClamp::VoltageClamp() {
}

VoltageClamp::VoltageClamp(VoltageEvent v_start, VoltageEvent v_step,
        VoltageEvent v_finish, VoltageEvent end) :
        v_start(v_start), v_step(v_step), v_finish(v_finish), end(end) {
}

void VoltageClamp::setVoltages(VoltageEvent v_start, VoltageEvent v_step,
        VoltageEvent v_finish, VoltageEvent end) {
    this->v_start = v_start;
    this->v_step = v_step;
    this->v_finish = v_finish;
    this->end = end;
}

double VoltageClamp::getVoltageAtTime(double time) {
    double voltage = 0;

    // Time before v_start
    if (time < 0) {
        voltage = 0; // Todo: Need to generate error here!
    }

    // Time during v_start
    else if (time >= v_start.getTimeInstant()
            && time < v_step.getTimeInstant()) {
        voltage = v_start.getNewVoltageValue();
    }

    // Time during v_step
    else if (time >= v_step.getTimeInstant()
            && time < v_finish.getTimeInstant()) {
        voltage = v_step.getNewVoltageValue();
    }

    // Time during v_finish
    else if (time >= v_finish.getTimeInstant() && time < end.getTimeInstant()) {
        voltage = v_finish.getNewVoltageValue();
    }

    // Time after v_end
    else if (time >= end.getTimeInstant()) {
        voltage = 0; // Todo: Need to generate error here!
    }

    else {
        ; // Should NOT get here!
    }

    return voltage;
}

