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

#include <ModFossa/ModelDefinition/Validation/ErrorLevel.h>
#include <ModFossa/ModelDefinition/Validation/ErrorType.h>

namespace ModFossa {
namespace Validation {

struct ValidationResults {
public:
    ValidationResults(ErrorLevel overall_result,
            std::vector< std::pair<ErrorType, std::string > > errors);
    virtual ~ValidationResults();

    const ErrorLevel overall_result;
    const std::vector< std::pair<ErrorType, std::string > > errors;
};
}
}

#endif	/* MARKOVMODELVALIDATIONRESULTS_H */

