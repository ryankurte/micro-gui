
#include "menu_window.h"

#include "ugui/ugui.h"
#include "ugui/font.h"

#include "ugui/widgets/menu_widget.h"

ugui_window_t *menu_window;

ugui_menu_widget_t *menu_widget;

/***			Internal Functions				***/

uint32_t example_menu_get_num_sections(void *menu_layer, void* data)
{
	return 0;
}

uint32_t example_menu_get_num_rows(void *menu_layer, void* data)
{
	return 4;
}

void example_menu_get_data(void* menu_layer, int index, char* title, char* data)
{
	char* faketitle = "test data title";
	char* fakedata = "test data content";
	//TODO: shit is unsafe.
	strncpy(title, faketitle, strlen(faketitle));
	strncpy(data, fakedata, strlen(fakedata));
}

void example_menu_select(void *menu_layer, ugui_menu_index_t *cell_index, void *callback_context)
{

}


/***			External Functions				***/

ugui_window_t *menu_window_create(uint32_t w, uint32_t h)
{
	menu_window = ugui_window_create(w, h);

	menu_widget = ugui_menu_widget_create((ugui_rect_t) {
		.w = w,
		.h = h
	});

	ugui_menu_widget_data_callbacks_t example_callbacks;
	example_callbacks.get_num_sections = example_menu_get_num_sections;
	example_callbacks.get_num_rows = example_menu_get_num_rows;
	example_callbacks.get_data = example_menu_get_data;
	example_callbacks.select = example_menu_select;

	ugui_menu_widget_set_callbacks(menu_widget, &example_callbacks);

	ugui_layer_t* base_layer = ugui_window_get_base_layer(menu_window);

	ugui_layer_t* widget_layer = ugui_menu_widget_get_layer(menu_widget);

	ugui_layer_add_child(base_layer, widget_layer);

	return menu_window;
}

void menu_window_destroy()
{


	ugui_window_destroy(menu_window);
}


