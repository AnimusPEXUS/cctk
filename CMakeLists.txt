cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

project(cctk)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)


find_package(Boost REQUIRED COMPONENTS json regex)

pkg_check_modules(sigc REQUIRED IMPORTED_TARGET sigc++-3.0)

find_package(ICU 73.0 COMPONENTS uc i18n REQUIRED)

add_subdirectory(types)
add_subdirectory(interfaces)
add_subdirectory(utils)

add_library(
	cctk
	CCTK.cpp
	Widget.cpp
	Form.cpp
	Button.cpp
    )

target_link_libraries(
	cctk 
	PUBLIC 
	cctk_types
	cctk_interfaces
	cctk_utils
	PRIVATE
	PkgConfig::sigc 
	Boost::json
	Boost::regex
	ICU::uc 
	ICU::i18n
    )

target_include_directories(
	cctk 
	PUBLIC 
	types
	interfaces
	utils
	PRIVATE
	${ICU_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
    )

