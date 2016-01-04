
#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <stdint.h>

#include "ugui/ugui.h"


typedef struct ugui_menu_index_s {
	uint32_t x;
	uint32_t y;
} ugui_menu_index_t;


typedef uint32_t menu_get_num_callback(void *menu_widget, void* data);
typedef uint32_t menu_get_height_callback(void *menu_widget, uint16_t section, void* data);

typedef void menu_get_header_callback(void* menu_widget, char* header);
typedef void menu_get_data_callback(void* menu_widget, uint16_t index, char* title, char* data);
typedef void menu_select_callback(void *menu_widget, uint16_t index, void *callback_context);

typedef void header_draw_callback(ugui_graphics_t *graphics_ctx, ugui_rect_t *bounds, char* title);
typedef void menu_draw_callback(ugui_graphics_t *graphics_ctx, ugui_rect_t *bounds, char* title, char* data);


typedef struct ugui_menu_widget_data_callbacks_s {
	menu_get_num_callback *get_num_sections;
	menu_get_num_callback *get_num_rows;

	menu_get_header_callback *get_header;
	menu_get_data_callback *get_data;

	menu_select_callback *select;

} ugui_menu_widget_data_callbacks_t;

typedef struct ugui_menu_widget_draw_callbacks_s {
	menu_get_num_callback *get_header_height;
	menu_get_num_callback *get_cell_height;

	header_draw_callback *draw_header;
	menu_draw_callback *draw_row;

} ugui_menu_widget_draw_callbacks_t;

typedef struct ugui_menu_widget_s ugui_menu_widget_t;

ugui_menu_widget_t *ugui_menu_widget_create(ugui_rect_t frame);

void ugui_menu_widget_set_callbacks(ugui_menu_widget_t* menu_widget, ugui_menu_widget_data_callbacks_t* callbacks);

void ugui_menu_widget_set_draw(ugui_menu_widget_t* menu_widget, ugui_menu_widget_draw_callbacks_t* callbacks);

ugui_layer_t* ugui_menu_widget_get_layer(ugui_menu_widget_t* menu_widget);

void ugui_menu_widget_attach_to_window(ugui_menu_widget_t* menu_widget, ugui_window_t* window);

void ugui_menu_widget_destroy(ugui_menu_widget_t* menu_widget);


#endif
