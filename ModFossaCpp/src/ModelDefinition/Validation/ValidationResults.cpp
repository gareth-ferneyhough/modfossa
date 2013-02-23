/* 
 * File:   MarkovModelValidationResults.cpp
 * Author: gareth
 * 
 * Created on February 23, 2013, 2:54 PM
 */

#include <ModelDefinition/Validation/ValidationResults.h>

namespace ModelDefinition {
    namespace Validation {

        ValidationResults::ValidationResults(ErrorLevel overall_result,
                vector< std::pair<ErrorType, string > > errors) :
        overall_result(overall_result),
        errors(errors) {
        }

        ValidationResults::~ValidationResults() {
        }
    }
}
