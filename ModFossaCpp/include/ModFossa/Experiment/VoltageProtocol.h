/* 
 * File:   VoltageProtocol.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:47 PM
 */

#ifndef VOLTAGEPROTOCOL_H
#define	VOLTAGEPROTOCOL_H

#include <string>
#include <vector>
#include <stdexcept>

#include <ModFossa/Common/SharedPtr.h>
#include <ModFossa/Experiment/SerializedVoltageProtocol.h>

namespace ModFossa {
class VoltageProtocol {
public:
    typedef ModFossa::shared_ptr<VoltageProtocol>::type SharedPointer;
    
    VoltageProtocol(std::string name);
    ~VoltageProtocol();
    
    /**
     * add constant voltage protocol stage to the VoltageProtocol. Constant
     * and stepped stages must be added in the desired order.
     * 
     * @param name name of the protocol stage
     * @param voltage stage voltage in mV
     * @param duration stage voltage in ms
     */
    void addConstantStage(std::string name, double voltage, double duration);
    
    /**
     * add stepped voltage protocol state to the VoltageProtocol. The voltage of 
     * a stepped stage begins at voltage_start, and steps by voltage_step mV 
     * until the voltage is equal to (or within less than voltage_step mV) to 
     * voltage_stop.
     * 
     * Constant and stepped stages must be added in the desired order. 
     * 
     * @param name name name of the protocol stage
     * @param voltage_start start voltage in mV
     * @param voltage_stop stop voltage in mV
     * @param voltage_step step voltage in mV
     * @param duration duration in ms
     */
    void addSteppedStage(std::string name, double voltage_start, 
        double voltage_stop, double voltage_step, double duration);
    
    std::string getName() const;

private:
    std::string name;
        
    void CheckNameNotEmpty(std::string name);
    void CheckDurationPositive(double duration);
    
    /**
     * Serialize the voltage protocol by returning a 2-D vector of time, voltage
     * pairs. The number 
     * @return 
     */
    SerializedVoltageProtocol serializeVoltageProtocol() const;
    friend class Experiment;
    
    /** 
     * Private nested class for storing both constant, and stepped 
     * VoltageProtocol stages. A constant protocol stage will have the same 
     * start and stop voltages, and a step of 0.
     */
    struct VoltageProtocolStage {
    VoltageProtocolStage(
            std::string name, 
            double start_voltage, 
            double stop_voltage, 
            double step_voltage, 
            double duration);
    
    std::string name;
    double start_voltage;
    double stop_voltage;
    double step_voltage;
    double duration;
    };
    
    std::vector<VoltageProtocolStage> voltage_protocol_stages;
};
}

#endif	/* VOLTAGEPROTOCOL_H */

