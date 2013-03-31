/* 
 * File:   VoltageProtocol.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 12:47 PM
 */

#include <utility>
#include <ModFossa/Experiment/VoltageProtocol.h>

namespace ModFossa {
VoltageProtocol::VoltageProtocol(std::string name) :
        name(name) {
    if (name.empty()) {
        throw std::runtime_error("VoltageProtocol name cannot be empty");
    }
    
    voltage_protocol_steps = VectorSharedPtr(new Vector());
}

VoltageProtocol::~VoltageProtocol() {
}

void VoltageProtocol::addConstantStage(std::string name, int voltage, 
        int duration) {

    // These two functions check the name and duration, and throw
    // runtime_errors if they are invalid.
    CheckNameNotEmpty(name);
    CheckDurationPositive(duration);
    
    // Because this is a constant stage, we will set the start and stop
    // voltages equal to voltage, and the voltage step to 0.
    int start = voltage;
    int stop = voltage;
    int step = 0;
  
    VoltageProtocolStage stage(name, start, stop, step, duration);
    voltage_protocol_stages.push_back(stage);
}
    
void VoltageProtocol::addSteppedStage(std::string name, int voltage_start, 
    int voltage_stop, int voltage_step, int duration) {
        
    // These functions will throw if there is a problem adding the stepped
    // stage
    CheckNoOtherSteppedStages();
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
    
    // Everything is awesome, so add the stage.
    VoltageProtocolStage stage(name, voltage_start, voltage_stop, 
            voltage_step, duration);
    voltage_protocol_stages.push_back(stage);
    
    // Finally, create and save vector of the step voltages. This is used by 
    // results class when calculating the IV curve.
    for(int v = voltage_start; v <= voltage_stop; v+= voltage_step) {
        voltage_protocol_steps->push_back(v);
    } 
}

void VoltageProtocol::CheckNameNotEmpty(std::string name) const {
    if (name.empty()) {
        throw std::runtime_error(
            "Error from " + this->name +
            ": VoltageProtocolStage name cannot be empty");
    }
}

void VoltageProtocol::CheckDurationPositive(int duration) const {
    if (!(duration > 0)) {
        throw std::runtime_error(
            "Error from " + this->name +
            ": VoltageProtocolStage duration must be positive");
    } 
}

void VoltageProtocol::CheckNoOtherSteppedStages() const {
    std::vector<VoltageProtocolStage>::const_iterator it;
    for(it = voltage_protocol_stages.begin(); 
            it != voltage_protocol_stages.end(); ++it) {
       
        if(it->step_voltage != 0) {
            throw std::runtime_error(
            "Error from " + this->name +
            ": only one stepped VoltageProtocolStage allowed in this version");
        }
    }
}


std::string VoltageProtocol::getName() const {
    return name;
}

bool VoltageProtocol::isEmpty() const {
    return voltage_protocol_stages.empty();
}

SerializedProtocolSharedPointer VoltageProtocol::serializeVoltageProtocol() {
    if(isEmpty()) {
        throw std::runtime_error(
                "Error from " + this->name +
                ": no VoltageProtocolStages defined");
    }
    
    // First, we need to get the number of steps in the stepped stage,
    // if any. This runs with the assumption that there is only one stepped 
    // stage defined. If there isn't a stepped stage defined, number of steps
    // should stay at 1.
    
    int number_of_steps = 1;
    std::vector<VoltageProtocolStage>::const_iterator it;
    for(it = voltage_protocol_stages.begin(); 
            it != voltage_protocol_stages.end(); ++it) {
      
        // Find the stepped stage if one exists
        if(it->step_voltage != 0) {
            number_of_steps = numberOfSteps(it->start_voltage, 
                    it->stop_voltage, it->step_voltage);
            break;
        }  
    }
    
    serialized_data = SerializedProtocolSharedPointer(new SerializedProtocol());
    //SerializedProtocol results; 
    
    // Now iterate through voltage_protocol_stages number_of_steps times and 
    // create the 2-D time,voltage pair structure.
    int current_time = 0;
    for(int step_index = 0; step_index < number_of_steps; ++step_index) {
        ProtocolIteration protocol_iteration;
        current_time = 0;
        
        // Iterate through voltage_protocol_stages, making a time, voltage
        // pair for each stage
        std::vector<VoltageProtocolStage>::const_iterator it;
        for(it = voltage_protocol_stages.begin(); 
            it != voltage_protocol_stages.end(); ++it) {

            protocol_iteration.push_back(makeTimeVoltagePair(
                *it, step_index, current_time));
            
            // Update time
            current_time += it->duration;
        }

        // We just added the final protocol stage, but we need to add one 
        // more time,voltage pair signify the end.
        protocol_iteration.push_back(makeTimeVoltagePair(
        (voltage_protocol_stages.back()), step_index, current_time));

        serialized_data->push_back(protocol_iteration);
    }
    
    return serialized_data;
}

VectorSharedPtr VoltageProtocol::getVoltageProtocolSteps() {
    return voltage_protocol_steps;
}

int VoltageProtocol::numberOfSteps(int start, int stop, int step) const {
    int difference = abs(stop - start);
    
    if(difference % step != 0) {
        /**
         * @todo Log or raise a warning
         */
        ;
    }
   
    return (difference / step) + 1;
}

std::pair<int, int> VoltageProtocol::makeTimeVoltagePair(
        VoltageProtocolStage stage, int step_index, int time) const {
    
    int voltage = stage.start_voltage + stage.step_voltage * step_index;
        
    return std::make_pair(time, voltage);   
}

VoltageProtocol::VoltageProtocolStage::VoltageProtocolStage(      
    std::string name, 
    int start_voltage, 
    int stop_voltage, 
    int step_voltage, 
    int duration) :
    name(name),
    start_voltage(start_voltage),
    stop_voltage(stop_voltage),
    step_voltage(step_voltage),
    duration(duration) {
}
}