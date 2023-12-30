cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
	cctk_types 
	ColorField.cpp
	)

target_link_libraries(
	cctk_types 
	PUBLIC 
	PkgConfig::sigc 
	Boost::json
	Boost::regex
	ICU::uc 
	ICU::i18n
    )

target_include_directories(
	cctk_types 
	PUBLIC 
	${Boost_INCLUDE_DIRS}
	${ICU_INCLUDE_DIRS}
    	)

