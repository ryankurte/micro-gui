
#include "ugui.h"

ugui_window_t *circle_window;
ugui_layer_t* circle_layer;


/***			Internal Functions				***/

static void circle_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	//Full size ellipse
	ugui_graphics_draw_ellipse(graphics_ctx, (ugui_rect_t) {
		.x = 0, .y = 0, .w = w - 1, .h = h - 1
	});

	//Circle
	int center_x = w / 2;
	int center_y = h / 2;
	int size = (h > w) ? w / 2 : h / 2;
	ugui_graphics_draw_ellipse(graphics_ctx, (ugui_rect_t) {
		.x = center_x - size / 2, .y = center_y - size / 2, .w = size, .h = size
	});

	ugui_layer_set_dirty(layer);
}

/***			External Functions				***/

ugui_window_t *circle_window_create(uint32_t w, uint32_t h)
{
	circle_window = ugui_window_create(w, h);

	circle_layer = ugui_layer_create((ugui_rect_t) {.x = 0, .y = 0, .w = w, .h = h});

	ugui_layer_t* base_layer = ugui_window_get_base_layer(circle_window);

	ugui_layer_set_update(circle_layer, circle_layer_update);

	ugui_layer_add_child(base_layer, circle_layer);

	return circle_window;
}

void circle_window_destroy()
{
	ugui_layer_destroy(circle_layer);

	ugui_window_destroy(circle_window);
}


