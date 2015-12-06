# MicroGUI CMake Library File

set(UGUI_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/buffer.c 
	${CMAKE_CURRENT_LIST_DIR}/source/sprite.c 
	${CMAKE_CURRENT_LIST_DIR}/source/window.c 
	${CMAKE_CURRENT_LIST_DIR}/source/layer.c 
	${CMAKE_CURRENT_LIST_DIR}/source/graphics.c 
	${CMAKE_CURRENT_LIST_DIR}/source/bmp.c 
	${CMAKE_CURRENT_LIST_DIR}/source/ugui.c
	${CMAKE_CURRENT_LIST_DIR}/source/font.c 
	)

set(UGUI_WIDGETS
	${CMAKE_CURRENT_LIST_DIR}/source/widgets/menu_widget.c
	)

set(UGUI_FONTS
	${CMAKE_CURRENT_LIST_DIR}/source/fonts/robotomono_regular_16.c 
	${CMAKE_CURRENT_LIST_DIR}/source/fonts/robotomono_regular_18.c
	)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(libugui ${UGUI_SOURCES} ${UGUI_FONTS} ${UGUI_WIDGETS})
