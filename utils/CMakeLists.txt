cmake_minimum_required(VERSION 3.14)

# project(cctk_utils)

include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

#get_filename_component(
#	cctk_types_path ../types
#	ABSOLUTE)

#message(STATUS "adding cctk_types")
#add_subdirectory("${cctk_types_path}" cctk_types_bin)

add_library(
	cctk_utils
	recursionGuard.cpp
	Property.cpp
	)

target_link_libraries(
	cctk_utils 
	PUBLIC 
	cctk_types
	)

target_include_directories(
	cctk_utils 
	PUBLIC 
	${Boost_INCLUDE_DIRS}
	${ICU_INCLUDE_DIRS}
	..
    	)
