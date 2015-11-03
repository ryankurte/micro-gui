
#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <stdint.h>

#include "ugui.h"


typedef struct ugui_menu_index_s {
	int32_t x;
	int32_t y;
} ugui_menu_index_t;


typedef int32_t (*menu_get_num_callback)(void *menu_layer, void* data);
typedef int16_t (*menu_get_height_callback)(void *menu_layer, uint16_t section, void* data);

typedef void (*menu_draw_callback)(ugui_graphics_t context, const ugui_layer_t cell_layer, uint16_t section_index, void* data);
typedef void (*menu_select_callback)(void *menu_layer, ugui_menu_index_t *cell_index, void *callback_context);

typedef struct ugui_menu_widget_callbacks_s {
	menu_get_num_callback get_num_sections;
	menu_get_num_callback get_num_rows;
	menu_get_height_callback get_header_height;
	menu_get_height_callback get_cell_height;
	menu_select_callback select;
	menu_draw_callback draw_header;
	menu_draw_callback draw_row;
} ugui_menu_widget_callbacks_t;

typedef struct ugui_menu_widget_s* ugui_menu_widget_t;

ugui_menu_widget_t ugui_menu_widget_create(ugui_rect_t frame);

void ugui_menu_widget_destroy(ugui_menu_widget_t menu_widget);


#endif
