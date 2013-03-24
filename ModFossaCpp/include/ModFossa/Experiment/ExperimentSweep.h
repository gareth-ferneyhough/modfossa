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
#include <ModFossa/Experiment/SerializedProtocol.h>
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Common/Concentration.h>

namespace ModFossa {
class ExperimentSweep {
public:
    typedef ModFossa::shared_ptr<ExperimentSweep>::type SharedPointer;
    typedef std::map<std::string, Concentration::SharedPointer> 
        ConcentrationMap;
    
    ExperimentSweep(
        const std::string name, 
        const std::string voltage_protocol_name, 
        ConcentrationMap concentration_map);
    
    ~ExperimentSweep();
    
    std::string getName() const;
    std::string getVoltageProtocolName() const;
    ConcentrationMap getConcentrationMap();
    SerializedProtocol getSerializedVoltageProtocol() const;
    
private:
    const std::string name;
    const std::string voltage_protocol_name;
    const ConcentrationMap concentration_map;
    SerializedProtocol serialized_voltage_protocol; 
    
    friend class Experiment;
    void setSerializedProtocol(SerializedProtocol 
        serialized_voltage_protocol);
};
}

#endif	/* EXPERIMENTSWEEP_H */

