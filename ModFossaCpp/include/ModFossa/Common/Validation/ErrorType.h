/* 
 * File:   MarkovModelErrorType.h
 * Author: gareth
 *
 * Created on February 23, 2013, 2:49 PM
 */

#ifndef MARKOVMODELERRORTYPE_H
#define	MARKOVMODELERRORTYPE_H

namespace ModFossa {
    namespace Validation {

        enum ErrorType {
            
            // MarkovModel Errors
            NO_CONNECTIONS, 
            MAX_CONDUCTANCE_NOT_DEFINED,
            MEMBRANE_CAPACITANCE_NOT_DEFINED,
            REVERSAL_POTENTIAL_NOT_DEFINED,
            RATE_CONSTANT_NOT_DEFINED,
            STATE_NOT_DEFINED, 
            LIGAND_NOT_DEFINED, 
            INITIAL_STATE_NOT_DEFINED,
            STATE_OF_THE_WORLD_IS_NULL,
            
            // Experiment Errors
            NO_VOLTAGE_PROTOCOLS,
            NO_EXPERIMENT_SWEEPS,
            VOLTAGE_PROTOCOL_NOT_DEFINED
        };
    }
}

#endif	/* MARKOVMODELERRORTYPE_H */

