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

#include <ModFossa/Common/Validation/ErrorLevel.h>
#include <ModFossa/Common/Validation/ErrorType.h>

namespace ModFossa {
namespace Validation {

struct ValidationResults {
public:
       
    /**
     * ErrorVector is a vector of ErrorType, and string pairs.
     * ErrorType is an enum, and the string is a description of the particular
     * ErrorType.
     * 
     */
    typedef std::vector< std::pair<ErrorType, std::string > > ErrorVector;
    
    ValidationResults(ErrorLevel overall_result, ErrorVector errors);       
    virtual ~ValidationResults();
    
    /**
     * Append an additional ValidationResults structure to this one. Set
     * the overall_result to the highest overall result of the two, and
     * append the errors from additional_results.errors to this instance.
     * 
     * @param additional_results
     * 
     * @todo This would be nice as an append operator, +=
     * 
     */
    void AppendAdditionalResults(const ValidationResults& additional_results);
    
    /**
     * @todo This should be const. They aren't right now due to the
     * implementation of the AppendAdditionalResults function.
     */
    ErrorLevel overall_result;
    
    /**
     * @todo This should be const. They aren't right now due to the
     * implementation of the AppendAdditionalResults function.
     */
    ErrorVector errors;
};
}
}

#endif	/* MARKOVMODELVALIDATIONRESULTS_H */

