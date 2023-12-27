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

add_library(
	cctk 
	CCTK.cpp
	WindowI.cpp
	SystemI.cpp
	WidgetI.cpp
	Widget.cpp
	Form.cpp
	Button.cpp
	# Label.cpp
	# TextEntry.cpp
    )

target_link_libraries(
    cctk 
    PUBLIC 
    PkgConfig::sigc 
    Boost::json
    Boost::regex
    ICU::uc 
    ICU::i18n
    )

target_include_directories(
    cctk 
    PUBLIC 
    ${Boost_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS}
    )

