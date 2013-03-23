/* 
 * File:   MarkovModelValidationResults.cpp
 * Author: gareth
 * 
 * Created on February 23, 2013, 2:54 PM
 */

#include <ModFossa/ModelDefinition/Validation/ValidationResults.h>

namespace ModFossa {
namespace Validation {

ValidationResults::ValidationResults(ErrorLevel overall_result,
    std::vector< std::pair<ErrorType, std::string > > errors) :
    overall_result(overall_result),
    errors(errors) {
}

ValidationResults::~ValidationResults() {
}
}
}
