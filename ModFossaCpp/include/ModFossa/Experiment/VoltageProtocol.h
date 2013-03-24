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
    void addConstantStage(std::string name, int voltage, int duration);
    
    /**
     * add stepped voltage protocol state to the VoltageProtocol. The voltage of 
     * a stepped stage begins at voltage_start, and steps by voltage_step mV 
     * until the voltage is equal to (or within less than voltage_step mV) to 
     * voltage_stop. Currently only one stepped stage can be added to a voltage
     * protocol.
     * 
     * Constant and stepped stages must be added in the desired order. 
     * 
     * @param name name name of the protocol stage
     * @param voltage_start start voltage in mV
     * @param voltage_stop stop voltage in mV
     * @param voltage_step step voltage in mV
     * @param duration duration in ms
     */
    void addSteppedStage(std::string name, int voltage_start, 
        int voltage_stop, int voltage_step, int duration);
    
    std::string getName() const;


    /**
     * Serialize the voltage protocol by returning a 2-D vector of time, voltage
     * pairs. The number of time, voltage pairs is equal to the number of 
     * stages. The size of the time, voltage pair vector is equal to the number
     * of steps in the stepped stage, or 1 if there is no stepped stage defined.
     *  
     * @return A SerializedVoltageProtocol as a 2-D vector of time, 
     * voltage pairs.
     */
    SerializedVoltageProtocol serializeVoltageProtocol() const;

private:   
    
    friend class Experiment;
    friend class VoltageProtocolTest;
    
    /** 
     * Private nested struct for storing both constant, and stepped 
     * VoltageProtocol stages. A constant protocol stage will have the same 
     * start and stop voltages, and a step of 0.
     */
    struct VoltageProtocolStage {
    VoltageProtocolStage(
            std::string name, 
            int start_voltage, 
            int stop_voltage, 
            int step_voltage, 
            int duration);
    
    std::string name;
    int start_voltage;
    int stop_voltage;
    int step_voltage;
    int duration;
    };
    
    std::vector<VoltageProtocolStage> voltage_protocol_stages;
    
    std::string name;
        
    void CheckNameNotEmpty(std::string name) const;
    void CheckDurationPositive(int duration) const;
    void CheckNoOtherSteppedStages() const;
    int numberOfSteps(int start, int stop, int step) const;
    std::pair<int, int> makeTimeVoltagePair(
        VoltageProtocolStage stage, int step_index, int current_time) const;
};
}

#endif	/* VOLTAGEPROTOCOL_H */

