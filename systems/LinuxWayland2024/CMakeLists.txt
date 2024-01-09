cmake_minimum_required(VERSION 3.14)

include_guard(GLOBAL)

project(cctk_sys_linux_wayland_2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

# set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)


find_package(Boost REQUIRED COMPONENTS json regex)

pkg_check_modules(sigc REQUIRED IMPORTED_TARGET sigc++-3.0)

pkg_check_modules(
	waylandpp 
	REQUIRED 
	IMPORTED_TARGET 
	wayland-client++ 
	wayland-client-extra++ 
	wayland-cursor++
	)

find_package(ICU 73.0 COMPONENTS uc i18n REQUIRED)

get_filename_component(cctk_abs_path ../..
                       ABSOLUTE)

add_subdirectory("${cctk_abs_path}" cctk_bin)

add_library(
	cctk_sys_linux_wayland_2024 
	System.cpp
	Window.cpp
	DrawingSurface.cpp
    )

target_link_libraries(
	cctk_sys_linux_wayland_2024 
	PUBLIC 
	PkgConfig::sigc 
	PkgConfig::waylandpp 
	Boost::json
	Boost::regex
	ICU::uc 
	ICU::i18n
	cctk
	)

target_include_directories(
	cctk_sys_linux_wayland_2024 
	PUBLIC 
	${Boost_INCLUDE_DIRS}
	${ICU_INCLUDE_DIRS}
	PkgConfig::waylandpp
	"${cctk_abs_path}"
	)

