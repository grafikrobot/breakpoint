cmake_minimum_required(VERSION 3.12)
project(debugging)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(debugging)

target_include_directories(debugging PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cxx)

target_sources(debugging PRIVATE ${SRC})
