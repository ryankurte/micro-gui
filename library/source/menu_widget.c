
#include "menu_widget.h"

struct ugui_menu_widget_s {
	ugui_menu_widget_callbacks_t callbacks;

} ugui_menu_widget_t;

void ugui_menu_widget_basic_header_draw(ugui_graphics_t grapics_context, ugui_layer_t layer, char* data)
{

}

void ugui_menu_widget_basic_cell_draw(ugui_graphics_t grapics_context, ugui_layer_t layer, char* title , char* data)
{

}

void ugui_menu_widget_set_callbacks(ugui_menu_widget_t menu_widget, ugui_menu_widget_callbacks_t callbacks)
{
	menu_widget->get_num_sections = callbacks.get_num_sections;
	menu_widget->get_num_rows = callbacks.get_num_rows;
	menu_widget->get_header_height = callbacks.get_header_height;
	menu_widget->get_cell_height = callbacks.get_cell_height;
	menu_widget->select = callbacks.select;
	menu_widget->draw_header = callbacks.draw_header;
	menu_widget->draw_row = callbacks.draw_row;
}

void ugui_menu_widget_attach_to_window(ugui_menu_widget_t menu_widget, ugui_window_t window)
{

}

void ugui_menu_widget_get_layer(ugui_menu_widget_t menu_widget)
{

}
