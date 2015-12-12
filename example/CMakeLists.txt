cmake_minimum_required (VERSION 2.8.11)

project (ugui-demo)

include(${CMAKE_CURRENT_SOURCE_DIR}/../ugui.cmake)

set(APP_SOURCES
	source/main.c 
	source/menu_window.c
	source/line_window.c 
	source/circle_window.c 
	source/layer_window.c
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable (${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} libmicro-gui SDL2)
