/* 
 * File:   ExperimentSweep.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:47 PM
 */

#ifndef EXPERIMENTSWEEP_H
#define	EXPERIMENTSWEEP_H

#include <string>
#include <vector>
#include <map>
#include <ModFossa/Experiment/SerializedVoltageProtocol.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Common/Concentration.h>

namespace ModFossa {
class ExperimentSweep {
public:
    typedef ModFossa::shared_ptr<ExperimentSweep>::type SharedPointer;
    typedef std::map<const std::string, Concentration::SharedPointer> 
        ConcentrationMap;
    
    ExperimentSweep(
        const std::string name, 
        const std::string voltage_protocol_name, 
        ConcentrationMap concentration_map);
    
    ~ExperimentSweep();
    
    std::string get_name() const;
    std::string get_voltage_protocol_name() const;
    ConcentrationMap get_concentration_map() const;
    SerializedVoltageProtocol get_serialized_voltage_protocol() const;
    
private:
    const std::string name;
    const std::string voltage_protocol_name;
    const ConcentrationMap concentration_map;
    SerializedVoltageProtocol serialized_voltage_protocol; 
    
    friend class Experiment;
    void setSerializedVoltageProtocol(SerializedVoltageProtocol 
        serialized_voltage_protocol);
};
}

#endif	/* EXPERIMENTSWEEP_H */

