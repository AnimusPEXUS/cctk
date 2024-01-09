cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL) 

project(cctk_interfaces)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

#get_filename_component(
#	cctk_types_path ..
#	ABSOLUTE)

#message(STATUS "adding cctk_types")
#add_subdirectory("${cctk_types_path}" cctk_types_bin)


add_library(
	cctk_interfaces
	INTERFACE
	)

target_include_directories(
	cctk_interfaces
	INTERFACE
	..
	)
