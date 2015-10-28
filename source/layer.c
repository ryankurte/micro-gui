
#include "layer.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct ugui_layer_s {
	ugui_rect_t bounds;
	ugui_layer_update_t update;
	bool dirty;
};

ugui_layer_t ugui_layer_create(ugui_rect_t bounds)
{
	ugui_layer_t layer = malloc(sizeof(struct ugui_layer_s));

	layer->bounds.x = bounds.x;
	layer->bounds.y = bounds.y;
	layer->bounds.w = bounds.w;
	layer->bounds.h = bounds.h;

	layer->update = NULL;

	return layer;
}

void ugui_layer_destroy(ugui_layer_t layer)
{
	free(layer);
}

ugui_rect_t* ugui_layer_get_bounds(ugui_layer_t layer)
{
	return &(layer->bounds);
}

void ugui_layer_add_child(ugui_layer_t layer, ugui_layer_t child)
{

}

void ugui_layer_set_update(ugui_layer_t layer, ugui_layer_update_t update)
{
	layer->update = update;
}

void ugui_layer_set_dirty(ugui_layer_t layer)
{
	layer->dirty = true;
}
