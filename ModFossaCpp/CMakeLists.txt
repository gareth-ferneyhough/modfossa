cmake_minimum_required (VERSION 2.8)
if(NOT cmake_build_type)
    set(cmake_build_type "debug")
endif()

project (ModFossa)


if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions("-Wall")
else()
    message(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
endif()


#find_package(Boost 1.48.0)
#if(Boost_FOUND)
#    include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python2.6")
#    set(Boost_USE_STATIC_LIBS OFF)
#    set(Boost_USE_MULTITHREADED ON)
#    set(Boost_USE_STATIC_RUNTIME OFF)
#    find_package(Boost 1.49.0 COMPONENTS log)
#elseif(NOT Boost_FOUND)
#    message(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
#endif()


set(EXTRA_LIBS ${EXTRA_LIBS} sundials_cvode sundials_nvecserial)
set(SRC_DIR    ${CMAKE_SOURCE_DIR}/src/)
set(INC_DIR    ${CMAKE_SOURCE_DIR}/include/)
set(TEST_DIR   ${CMAKE_SOURCE_DIR}/test/)
set(SAMPLE_DIR ${CMAKE_SOURCE_DIR}/samples/)

#set(CMAKE_CXX_FLAGS "-Wall -W -Wshadow -pedantic-errors -pedantic -Wextra -Werror")
set(CMAKE_CXX_FLAGS "-std=c++0x -g")

include_directories(${INC_DIR})
  
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

add_library(ModFossa SHARED ${SRC_FILES})
target_link_libraries (ModFossa ${EXTRA_LIBS} )#${Boost_LIBRARIES})

################################
# Documentation
################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

################################
# Samples
################################
file(GLOB SAMPLE_FILES ${SAMPLE_DIR}/*.cpp)
add_executable(samples ${SAMPLE_FILES})
target_link_libraries(samples ModFossa)

################################
# GTest
################################
ADD_SUBDIRECTORY (dependencies/gtest-1.6.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
add_executable( runUnitTests ${TEST_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main ModFossa)
add_test( runUnitTests runUnitTests )


install (TARGETS ModFossa DESTINATION .)


