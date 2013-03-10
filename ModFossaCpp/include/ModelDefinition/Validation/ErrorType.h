/* 
 * File:   MarkovModelErrorType.h
 * Author: gareth
 *
 * Created on February 23, 2013, 2:49 PM
 */

#ifndef MARKOVMODELERRORTYPE_H
#define	MARKOVMODELERRORTYPE_H

namespace ModelDefinition {
    namespace Validation {

        enum ErrorType {
            NO_CONNECTIONS, RATE_CONSTANT_NOT_DEFINED,
            STATE_NOT_DEFINED, LIGAND_NOT_DEFINED, INITIAL_STATE_NOT_DEFINED,
			STATE_OF_THE_WORLD_IS_NULL
        };
    }
}

#endif	/* MARKOVMODELERRORTYPE_H */

