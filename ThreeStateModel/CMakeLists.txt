cmake_minimum_required (VERSION 2.8)
if(NOT cmake_build_type)
	set(cmake_build_type "debug")
endif()

project (ModFossa)
  
find_package(Boost 1.49.0)
if(Boost_FOUND)
	include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python2.6")
	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME OFF)
	find_package(Boost 1.49.0 COMPONENTS python)
	
 	add_subdirectory (src)
  
elseif(NOT Boost_FOUND)
    message(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions("-Wall")
else()
    message(FATAL_ERROR "CMakeLists.txt has not been tested/written for your compiler.")
endif()    
