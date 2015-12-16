# CMake Build File

cmake_minimum_required (VERSION 2.8.11)

project (ugui)

include(${CMAKE_CURRENT_SOURCE_DIR}/ugui.cmake)

set(APP_SOURCES
	example/source/main.c 
	example/source/menu_window.c
	example/source/line_window.c 
	example/source/circle_window.c 
	example/source/layer_window.c
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/example/include)

add_executable (${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} libugui SDL2)