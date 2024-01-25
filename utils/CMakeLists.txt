cmake_minimum_required(VERSION 3.14)

# project(cctk_utils)

include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(sigc REQUIRED IMPORTED_TARGET sigc++-3.0)

#get_filename_component(
#	cctk_types_path ../types
#	ABSOLUTE)

#message(STATUS "adding cctk_types")
#add_subdirectory("${cctk_types_path}" cctk_types_bin)

add_library(
	cctk_utils
	PRIVATE
	MemFD.cpp
	)

#target_link_libraries(
#	cctk_utils 
#	)

target_include_directories(
	cctk_utils 
	PRIVATE 
	${Boost_INCLUDE_DIRS}
	${ICU_INCLUDE_DIRS}
	${sigc_INCLUDE_DIRS}
	..
    	)
