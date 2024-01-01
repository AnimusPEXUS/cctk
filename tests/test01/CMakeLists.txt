cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

project(cctk_test_01)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_filename_component(
	cctk_abs_path ../..
	ABSOLUTE)

get_filename_component(
	cctk_sys_abs_path ../../systems/LinuxWayland2024
	ABSOLUTE)

get_filename_component(
	cctk_laf_abs_path ../../laf/memphis 
	ABSOLUTE)

message(STATUS "cctk path:     ${cctk_abs_path}")
message(STATUS "cctk_sys path: ${cctk_sys_abs_path}")
message(STATUS "cctk_laf path: ${cctk_laf_abs_path}")

message(STATUS "adding cctk")
add_subdirectory("${cctk_abs_path}" cctk_bin)

message(STATUS "adding system")
add_subdirectory("${cctk_sys_abs_path}" cctk_sys_bin)

message(STATUS "adding laf")
add_subdirectory("${cctk_laf_abs_path}" cctk_laf_bin)

add_executable(
	cctk_test_01 
	Test01.cpp
	)

target_link_libraries(
	cctk_test_01 
	PUBLIC 
	cctk
	cctk_sys_linux_wayland_2024 
	cctk_laf_memphis
	)

target_include_directories(
	cctk_test_01
	PUBLIC 
	"."
	"${cctk_abs_path}"
	"${cctk_sys_abs_path}"
	"${cctk_laf_abs_path}"
	)
