/* 
 * File:   ExperimentSweep.cpp
 * Author: gareth
 * 
 * Created on March 23, 2013, 12:47 PM
 */

#include <ModFossa/Experiment/ExperimentSweep.h>

namespace ModFossa {

ExperimentSweep::ExperimentSweep(
        const std::string name,
        const std::string voltage_protocol_name,
        ConcentrationMap concentration_map) :
name(name),
voltage_protocol_name(voltage_protocol_name) {

}

ExperimentSweep::~ExperimentSweep() {
}

ExperimentSweep::ConcentrationMap ExperimentSweep::getConcentrationMap() {

}

std::string ExperimentSweep::getName() const {
    return name;
}
}

