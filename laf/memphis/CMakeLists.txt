cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

project(cctk_laf_memphis)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# set(Boost_USE_STATIC_LIBS        ON)
# set(Boost_USE_DEBUG_LIBS        OFF)
# set(Boost_USE_RELEASE_LIBS       ON)
# set(Boost_USE_MULTITHREADED      ON)

# find_package(Boost REQUIRED COMPONENTS json regex)

pkg_check_modules(sigc REQUIRED IMPORTED_TARGET sigc++-3.0)

find_package(ICU 73.0 COMPONENTS uc i18n REQUIRED)

get_filename_component(cctk_abs_path ../..
                       ABSOLUTE)

add_subdirectory("${cctk_abs_path}" cctk_bin)

add_library(
	cctk_laf_memphis 
	cctk_laf_memphis.cpp
    )

target_link_libraries(
    cctk_laf_memphis 
    PUBLIC 
    PkgConfig::sigc 
    ICU::uc 
    ICU::i18n
	cctk
    )

target_include_directories(
    cctk_laf_memphis 
    PUBLIC 
    ${ICU_INCLUDE_DIRS}
	cctk
    )

