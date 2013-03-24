/* 
 * File:   ValidationResults.cpp
 * Author: gareth
 * 
 * Created on February 23, 2013, 2:54 PM
 */

#include <ModFossa/Common/Validation/ValidationResults.h>

namespace ModFossa {
namespace Validation {

ValidationResults::ValidationResults(ErrorLevel overall_result,
    std::vector< std::pair<ErrorType, std::string > > errors) :
    overall_result(overall_result),
    errors(errors) {
}

ValidationResults::~ValidationResults() {
}

void ValidationResults::AppendAdditionalResults(
        const ValidationResults& additional_results) {

    // First, set the overall combined results to the highest error level
    // out of the two results we are combining. overall_result is an enum,
    // so we can use comparison operators.
    
    if(additional_results.overall_result > this->overall_result) {
        this->overall_result = additional_results.overall_result;
    }
    
    // Now append the additional errors to our errors vector.
    ErrorVector::const_iterator it;
    for(it = additional_results.errors.begin(); 
            it != additional_results.errors.end(); ++it) {
        this->errors.push_back(*it);
    }
}

}
}
