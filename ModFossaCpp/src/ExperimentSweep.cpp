/* 
 * File:   ExperimentSweep.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 12:47 PM
 */

#include <ModFossa/Experiment/ExperimentSweep.h>

namespace ModFossa {

/**
 * @todo check for empty names
 * 
 * @param name
 * @param voltage_protocol_name
 * @param concentration_map
 */
ExperimentSweep::ExperimentSweep(
        const std::string name,
        const std::string voltage_protocol_name,
        ConcentrationMap concentration_map) :
name(name),
voltage_protocol_name(voltage_protocol_name) {

}

ExperimentSweep::~ExperimentSweep() {
}

ExperimentSweep::ConcentrationMap 
        ExperimentSweep::getConcentrationMap() const {
    
    return concentration_map;
}

std::string ExperimentSweep::getName() const {
    return name;
}

std::string ExperimentSweep::getVoltageProtocolName() const {
    return voltage_protocol_name;
}

void ExperimentSweep::setSerializedProtocol(SerializedProtocolSharedPointer 
    serialized_voltage_protocol) {
    
    this->serialized_voltage_protocol = serialized_voltage_protocol;
}
}

