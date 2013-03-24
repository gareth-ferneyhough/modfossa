/* 
 * File:   VoltageProtocol.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 12:47 PM
 */

#include <ModFossa/Experiment/VoltageProtocol.h>

namespace ModFossa {
VoltageProtocol::VoltageProtocol(std::string name) :
        name(name) {
    if (name.empty()) {
        throw std::runtime_error("VoltageProtocol name cannot be empty");
    }
}

VoltageProtocol::~VoltageProtocol() {
}

void VoltageProtocol::addConstantStage(std::string name, double voltage, 
        double duration) {

    // These two functions check the name and duration, and throw
    // runtime_errors if they are invalid.
    CheckNameNotEmpty(name);
    CheckDurationPositive(duration);
    
    // Because this is a constant stage, we will set the start and stop
    // voltages equal to voltage, and the voltage step to 0.
    double start = voltage;
    double stop = voltage;
    double step = 0;
  
    VoltageProtocolStage stage(name, start, stop, step, duration);
    voltage_protocol_stages.push_back(stage);
}
    

void VoltageProtocol::addSteppedStage(std::string name, double voltage_start, 
    double voltage_stop, double voltage_step, double duration) {

    // These two functions check the name and duration, and throw
    // runtime_errors if they are invalid.
    CheckNameNotEmpty(name);
    CheckDurationPositive(duration);
    
    // Make sure that voltage_step is not 0
    if(voltage_step == 0) {
        throw std::runtime_error(
                "Error from " + this->name +
                ": voltage_step cannot be zero");
    }
    
    // Make sure that voltage_step has the correct sign
    if(((voltage_stop < voltage_start) && (voltage_step > 0)) || 
      ((voltage_stop > voltage_start) && (voltage_step < 0))) {
        throw std::runtime_error(
                "Error from " + this->name +
                ": voltage_step has incorrect sign");
    }
    
    //Everything is awesome, so add the stage.
    VoltageProtocolStage stage(name, voltage_start, voltage_stop, 
            voltage_step, duration);
    voltage_protocol_stages.push_back(stage);
}

void VoltageProtocol::CheckNameNotEmpty(std::string name) {
    if (name.empty()) {
        throw std::runtime_error(
            "Error from " + this->name +
            ": VoltageProtocolStage name cannot be empty");
    }
}

void VoltageProtocol::CheckDurationPositive(double duration) {
    if (!(duration > 0)) {
        throw std::runtime_error(
            "Error from " + this->name +
            ": VoltageProtocolStage duration must be positive");
    } 
}

std::string VoltageProtocol::getName() const {
    return name;
}

VoltageProtocol::VoltageProtocolStage::VoltageProtocolStage(      
    std::string name, 
    double start_voltage, 
    double stop_voltage, 
    double step_voltage, 
    double duration) :
    name(name),
    start_voltage(start_voltage),
    stop_voltage(stop_voltage),
    step_voltage(step_voltage) {
}
}