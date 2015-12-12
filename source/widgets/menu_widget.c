
#include "ugui/widgets/menu_widget.h"

#include <stdlib.h>

struct ugui_menu_widget_s {
	ugui_layer_t* widget_layer;
	ugui_menu_widget_draw_callbacks_t draw_callbacks;
	ugui_menu_widget_data_callbacks_t data_callbacks;
	int selected;
};

static void menu_widget_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
	ugui_menu_widget_t* menu_widget = (ugui_menu_widget_t*) layer_ctx;

	menu_widget->draw_callbacks.draw_header(graphics_ctx, layer, "Test title");

	char* title;
	char* data;

#if 0
	for (uint8_t i = 0; i < menu_widget->data_callbacks.get_num_rows(); i++) {
		menu_widget->data_callbacks.
	}
#endif
}

void ugui_menu_widget_basic_header_draw(ugui_graphics_t *graphics_ctx, ugui_layer_t *layer, char* title)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	ugui_size_t text_size;
	ugui_font_get_text_size(&font_robotomono_regular_18,
	                        title,
	                        &text_size);

	ugui_graphics_draw_text(graphics_ctx,
	                        title,
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = w / 2 - text_size.w / 2, .y = 0
	});
}

void ugui_menu_widget_basic_cell_draw(ugui_graphics_t* graphics_ctx, ugui_layer_t* layer, char* title , char* data)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	ugui_size_t title_size;
	ugui_font_get_text_size(&font_robotomono_regular_18,
	                        title,
	                        &title_size);

	ugui_graphics_draw_text(graphics_ctx,
	                        title,
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = w / 2 - title_size.w / 2, .y = 0
	});

	ugui_size_t data_size;
	ugui_font_get_text_size(&font_robotomono_regular_18,
	                        data,
	                        &data_size);

	ugui_graphics_draw_text(graphics_ctx,
	                        data,
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = w / 2 - data_size.w / 2, .y = title_size.h + 16
	});
}

ugui_menu_widget_t *ugui_menu_widget_create(ugui_rect_t bounds) {
	ugui_menu_widget_t* menu_widget = (ugui_menu_widget_t*)malloc(sizeof(ugui_menu_widget_t));

	menu_widget->widget_layer = ugui_layer_create(bounds);

	menu_widget->selected = 0;

	menu_widget->draw_callbacks.draw_header = ugui_menu_widget_basic_header_draw;
	menu_widget->draw_callbacks.draw_row = ugui_menu_widget_basic_cell_draw;

	ugui_layer_set_update(menu_widget->widget_layer, menu_widget_layer_update);

	ugui_layer_set_ctx(menu_widget->widget_layer, (void*) menu_widget);

	return menu_widget;
}

void ugui_menu_widget_set_callbacks(ugui_menu_widget_t* menu_widget, ugui_menu_widget_data_callbacks_t* callbacks)
{
	menu_widget->data_callbacks.get_num_sections = callbacks->get_num_sections;
	menu_widget->data_callbacks.get_num_rows = callbacks->get_num_rows;
	menu_widget->data_callbacks.get_header_height = callbacks->get_header_height;
	menu_widget->data_callbacks.get_cell_height = callbacks->get_cell_height;
	menu_widget->data_callbacks.select = callbacks->select;
}

void ugui_menu_widget_set_draw(ugui_menu_widget_t* menu_widget, ugui_menu_widget_draw_callbacks_t* callbacks)
{
	menu_widget->draw_callbacks.draw_header = callbacks->draw_header;
	menu_widget->draw_callbacks.draw_row = callbacks->draw_row;
}

void ugui_menu_widget_attach_to_window(ugui_menu_widget_t* menu_widget, ugui_window_t* window)
{

}

ugui_layer_t* ugui_menu_widget_get_layer(ugui_menu_widget_t* menu_widget)
{
	return menu_widget->widget_layer;
}
