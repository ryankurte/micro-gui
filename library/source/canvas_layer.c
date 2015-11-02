
#include "canvas_layer.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "layer.h"

struct ugui_canvas_layer_s {
	ugui_layer_t base_layer;
};

ugui_canvas_layer_t ugui_canvas_layer_create(ugui_rect_t bounds)
{
	ugui_canvas_layer_t layer = malloc(sizeof(struct ugui_canvas_layer_s));

	layer->base_layer = ugui_layer_create(bounds);

	return layer;
}

void ugui_canvas_layer_destroy(ugui_canvas_layer_t layer)
{
	free(layer);
}

void ugui_canvas_layer_get_bounds(ugui_canvas_layer_t layer)
{
	
}

void ugui_canvas_layer_add_child(ugui_canvas_layer_t layer, ugui_canvas_layer_t child)
{

}

void ugui_canvas_layer_set_update(ugui_canvas_layer_t layer, ugui_layer_update_t update)
{
	ugui_layer_set_update(layer->base_layer, update);
}

void ugui_canvas_layer_set_dirty(ugui_canvas_layer_t layer)
{
	ugui_layer_set_dirty(layer->base_layer);
}
