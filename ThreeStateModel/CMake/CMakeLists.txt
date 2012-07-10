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


find_package(Boost 1.49.0)
if(Boost_FOUND)
    include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python2.6")
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    find_package(Boost 1.49.0 COMPONENTS python)
elseif(NOT Boost_FOUND)
    message(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
endif()


set(EXTRA_LIBS ${EXTRA_LIBS} sundials_cvode sundials_nvecserial)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src/)
set(INC_DIR ${CMAKE_SOURCE_DIR}/../include/)

#set(CMAKE_CXX_FLAGS "-Wall -W -Wshadow -pedantic-errors -pedantic -Wextra -Werror")

include_directories(${INC_DIR})
  
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

add_library(ModFossa SHARED ${SRC_FILES})
target_link_libraries (ModFossa ${EXTRA_LIBS} ${Boost_LIBRARIES})



install (TARGETS ModFossa DESTINATION .)



option(BUILD_DOCUMENTATION "Build Documentation" ON)

if(BUILD_DOCUMENTATION)
    add_custom_target (Documentation ALL)
    add_custom_command(
        COMMAND   doxygen ${CMAKE_SOURCE_DIR}/Doxyfile > /dev/null
        TARGET    Documentation
    )
endif(BUILD_DOCUMENTATION)