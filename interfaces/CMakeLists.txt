cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL) 

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

add_library(
	cctk_interfaces
	INTERFACE
	)

target_include_directories(
	cctk_interfaces
	INTERFACE
	.
	)
	
