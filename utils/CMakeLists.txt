cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

add_library(
	cctk_utils
	recursionGuard.cpp
	)

target_link_libraries(
	cctk_utils 
	PUBLIC 
	PkgConfig::sigc 
	Boost::json
	Boost::regex
	ICU::uc 
	ICU::i18n
	cctk_types
	)

target_include_directories(
	cctk_utils 
	PUBLIC 
	${Boost_INCLUDE_DIRS}
	${ICU_INCLUDE_DIRS}
	cctk_types
    	)
