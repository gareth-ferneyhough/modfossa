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
#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Common/Concentration.h>

namespace ModFossa {
class ExperimentSweep {
public:
    typedef ModFossa::shared_ptr<ExperimentSweep>::type SharedPointer;
    typedef std::map<const std::string, Concentration::SharedPointer> 
        ConcentrationMap;
    
    ExperimentSweep();
    ~ExperimentSweep();
private:
    std::string voltage_protocol_name;
    ConcentrationMap concentration_map;

};
}

#endif	/* EXPERIMENTSWEEP_H */

