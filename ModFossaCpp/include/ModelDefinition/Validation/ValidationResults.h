/* 
 * File:   MarkovModelValidationResults.h
 * Author: gareth
 *
 * Created on February 23, 2013, 2:54 PM
 */

#ifndef MARKOVMODELVALIDATIONRESULTS_H
#define	MARKOVMODELVALIDATIONRESULTS_H

#include <utility>
#include <vector>
#include <string>

#include <ModelDefinition/Validation/ErrorLevel.h>
#include <ModelDefinition/Validation/ErrorType.h>

using std::string;
using std::vector;

namespace ModelDefinition {
    namespace Validation {

        struct ValidationResults {
        public:
            ValidationResults(ErrorLevel overall_result,
                    vector< std::pair<ErrorType, string > > errors);
            virtual ~ValidationResults();

            const ErrorLevel overall_result;
            const vector< std::pair<ErrorType, string > > errors;
        };
    }
}

#endif	/* MARKOVMODELVALIDATIONRESULTS_H */

