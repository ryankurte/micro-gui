
#include "window.h"

#include <stdlib.h>

#include "layer.h"
#include "types.h"

struct ugui_window_s {
	ugui_layer_t base_layer;
	ugui_window_handlers_t handlers;
};

ugui_window_t ugui_window_create(uint32_t w, uint32_t h)
{
	ugui_window_t window = malloc(sizeof(struct ugui_window_s));

	window->base_layer = ugui_layer_create((ugui_rect_t) {
		.x = 0, .y = 0, .w = w, .h = h
	});

	window->handlers.load = NULL;
	window->handlers.unload = NULL;

	return window;
}

ugui_layer_t ugui_window_get_base_layer(ugui_window_t window)
{
	return window->base_layer;
}

void ugui_window_set_window_handlers(ugui_window_t window,
                                     ugui_window_handlers_t handlers)
{
	window->handlers.load = handlers.load;
	window->handlers.unload = handlers.unload;
}

void ugui_window_destroy(ugui_window_t window)
{
	ugui_layer_destroy(window->base_layer);

	free(window);
}


void ugui_window_load(ugui_window_t window)
{
	window->handlers.load(window);
}

void ugui_window_unload(ugui_window_t window)
{
	window->handlers.unload(window);
}
