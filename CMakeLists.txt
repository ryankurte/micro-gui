# CMake Build File

cmake_minimum_required (VERSION 2.8.7)

project (ugui)


# Find SDL2 if required
if(NOT DEFINED NO_SDL2)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(SDL2 REQUIRED)
add_definitions("-DUSE_SDL2=1")
endif()

include_directories(${SDL2_INCLUDE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/ugui.cmake)

set(CMAKE_C_FLAGS "-std=gnu11")

set(APP_SOURCES
	example/source/main.c 
	example/source/menu_window.c
	example/source/line_window.c 
	example/source/circle_window.c 
	example/source/layer_window.c
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/example/include)

add_executable (${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} libugui ${SDL2_LIBRARY})
