
#include "menu_window.h"

#include "ugui/ugui.h"
#include "ugui/font.h"

#include "ugui/widgets/menu_widget.h"

ugui_window_t *menu_window;

ugui_menu_widget_t *menu_widget;

/***			Internal Functions				***/



/***			External Functions				***/

ugui_window_t *menu_window_create(uint32_t w, uint32_t h)
{
	menu_window = ugui_window_create(w, h);

	menu_widget = ugui_menu_widget_create((ugui_rect_t) {
		.w = w,
		.h = h
	});


	ugui_layer_t* base_layer = ugui_window_get_base_layer(menu_window);

	ugui_layer_t* widget_layer = ugui_menu_widget_get_layer(menu_widget);

	ugui_layer_add_child(base_layer, widget_layer);


	return menu_window;
}

void menu_window_destroy()
{
	

	ugui_window_destroy(menu_window);
}


