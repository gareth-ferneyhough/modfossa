/*
 * VoltageEvent.h
 *
 *  Created on: Jul 12, 2012
 *      Author: gareth
 */

#ifndef VOLTAGEEVENT_H_
#define VOLTAGEEVENT_H_

class VoltageEvent {
public:
    VoltageEvent() :
            time_instant(-1), new_voltage_value(-1) {
    }

    VoltageEvent(double time, double voltage) :
            time_instant(time), new_voltage_value(voltage) {
    }

    double getNewVoltageValue() const {
        return new_voltage_value;
    }

    void setNewVoltageValue(double newVoltageValue) {
        new_voltage_value = newVoltageValue;
    }

    double getTimeInstant() const {
        return time_instant;
    }

    void setTimeInstant(double timeInstant) {
        time_instant = timeInstant;
    }

private:
    double time_instant;
    double new_voltage_value;
};

#endif /* VOLTAGEEVENT_H_ */
