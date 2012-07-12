/*
 * VoltageClamp.h
 *
 *  Created on: Jul 12, 2012
 *      Author: gareth
 */

#ifndef VOLTAGECLAMP_H_
#define VOLTAGECLAMP_H_

#include <ModFossa/VoltageEvent.h>

class VoltageClamp {
public:
    VoltageClamp();
    VoltageClamp(VoltageEvent v_start, VoltageEvent v_step,
            VoltageEvent v_finish, VoltageEvent end);

    void setVoltages(VoltageEvent v_start, VoltageEvent v_step,
            VoltageEvent v_finish, VoltageEvent end);

    double getVoltageAtTime(double time);

private:
    VoltageEvent v_start;
    VoltageEvent v_step;
    VoltageEvent v_finish;
    VoltageEvent end;
};

#endif /* VOLTAGECLAMP_H_ */
