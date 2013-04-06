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

find_package(Boost COMPONENTS python chrono REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs 2.7 REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )


set(EXTRA_LIBS ${EXTRA_LIBS} sundials_cvode sundials_nvecserial armadillo)
set(SRC_DIR    ${CMAKE_SOURCE_DIR}/src/)
set(INC_DIR    ${CMAKE_SOURCE_DIR}/include/)
set(TEST_DIR   ${CMAKE_SOURCE_DIR}/test/)
set(SAMPLE_DIR ${CMAKE_SOURCE_DIR}/samples/)

#set(CMAKE_CXX_FLAGS "-Wall -W -Wshadow -pedantic-errors -pedantic -Wextra -Werror")
set(CMAKE_CXX_FLAGS "-std=c++0x -g")
  
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

add_library(ModFossa SHARED ${SRC_FILES})
set_target_properties(ModFossa PROPERTIES PREFIX "")

include_directories(ModFossa
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${INC_DIR}
)

target_link_libraries(ModFossa
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${EXTRA_LIBS}
)

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


