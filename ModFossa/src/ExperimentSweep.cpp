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
        const std::string voltage_protocol_name)://,
        //ConcentrationMap concentration_map) :
name(name),
voltage_protocol_name(voltage_protocol_name){
//concentration_map(concentration_map) {
    
    if (name.empty()) {
        throw std::runtime_error("ExperimentSweep name cannot be empty");
    }
    
    if (voltage_protocol_name.empty()) {
        throw std::runtime_error("voltage_protocol_name name cannot be empty");
    }
}

ExperimentSweep::~ExperimentSweep() {
}

ExperimentSweep::ConcentrationMap 
        ExperimentSweep::getConcentrationMap() const {
    
    return concentration_map;
}

void ExperimentSweep::addConcentration(Concentration concentration) {
    if (concentrationExists(concentration.ligand_name)) {
        throw std::runtime_error(
                "Concentration for ligand " + 
                concentration.ligand_name + " already exists");
    }
    
    concentration_map[concentration.ligand_name] = 
            make_shared<Concentration>(concentration);
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

SerializedProtocolSharedPointer 
        ExperimentSweep::getSerializedVoltageProtocol() const {
    return serialized_voltage_protocol;
}

bool ExperimentSweep::concentrationExists(std::string name) const {
    ConcentrationMap::const_iterator it;
    it = concentration_map.find(name);

    if (it != concentration_map.end()) {
        return true;
    }
    return false;
}
}

