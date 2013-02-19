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


set(EXTRA_LIBS ${EXTRA_LIBS} )
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src/)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include/)

#set(CMAKE_CXX_FLAGS "-Wall -W -Wshadow -pedantic-errors -pedantic -Wextra -Werror")

include_directories(${INC_DIR})
  
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

add_library(ModFossa SHARED ${SRC_FILES})
target_link_libraries (ModFossa ${EXTRA_LIBS})

################################
# GTest
################################
ADD_SUBDIRECTORY (dependencies/gtest-1.6.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runUnitTests test/ConstantRateConstantTest.cpp test/StateOfTheWorldTest.cpp test/SigmoidalRateConstantTest.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main ModFossa)
add_test( runUnitTests runUnitTests )


install (TARGETS ModFossa DESTINATION .)


