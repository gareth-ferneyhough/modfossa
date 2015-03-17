#include <gtest/gtest.h>
#include <ModFossa/Common/Validation/ValidationResults.h>

using namespace ModFossa;
using namespace Validation;

class ValidationResultsTest : public testing::Test {
protected:

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }
};

/**
 * Test Case X.1 - Create ValidationResults Success
 * Use Case: X.1 - Main Success Scenario
 */
TEST_F(ValidationResultsTest, createValidationResults) {
    
    ValidationResults::ErrorVector errors1;
    ErrorLevel level1 = NO_WARNINGS;
    ValidationResults results1(level1, errors1);
    
    ASSERT_EQ(results1.overall_result, level1);
    ASSERT_EQ(results1.errors, errors1);
     
    ValidationResults::ErrorVector errors2;
    ErrorLevel level2 = ERRORS;
    
    errors2.push_back(std::make_pair(
        NO_CONNECTIONS, 
        "No connections"));
    
    errors2.push_back(std::make_pair(
        NO_VOLTAGE_PROTOCOLS, 
        "No voltage protocol"));
    
    ValidationResults results2(level2, errors2);    
    results1.AppendAdditionalResults(results2);
    
    ASSERT_EQ(results1.overall_result, level2);
    ASSERT_EQ(results1.errors, errors2);   
    
    
}





















































