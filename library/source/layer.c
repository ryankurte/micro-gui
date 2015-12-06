
#include "layer.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "graphics.h"

#define UGUI_LAYER_MAX_CHILDREN		8

struct ugui_layer_s {
	ugui_rect_t bounds;
	ugui_layer_update_t update;
	bool dirty;
	void* ctx;
	ugui_layer_t *children[UGUI_LAYER_MAX_CHILDREN];
};

/***			Public				***/

ugui_layer_t* ugui_layer_create(ugui_rect_t bounds)
{
	ugui_layer_t* layer = malloc(sizeof(struct ugui_layer_s));

	layer->bounds.x = bounds.x;
	layer->bounds.y = bounds.y;
	layer->bounds.w = bounds.w;
	layer->bounds.h = bounds.h;

	layer->update = NULL;

	for(int i=0; i<UGUI_LAYER_MAX_CHILDREN; i++) {
		layer->children[i] = 0;
	}

	return layer;
}

void ugui_layer_destroy(ugui_layer_t* layer)
{
	free(layer);
}

ugui_rect_t* ugui_layer_get_bounds(ugui_layer_t* layer)
{
	return &(layer->bounds);
}

int32_t ugui_layer_add_child(ugui_layer_t* layer, ugui_layer_t *child)
{
	for (uint8_t i = 0; i < UGUI_LAYER_MAX_CHILDREN; i++) {
		if (layer->children[i] == NULL) {
			layer->children[i] = child;
			return 1;
		}
	}
	return 0;
}

void ugui_layer_set_ctx(ugui_layer_t* layer, void* ctx) {
	layer->ctx = ctx;
}

void ugui_layer_set_update(ugui_layer_t* layer, ugui_layer_update_t update)
{
	layer->update = update;
}

void ugui_layer_set_dirty(ugui_layer_t* layer)
{
	layer->dirty = true;
}

/***			Private				***/

int _ugui_layer_update(ugui_layer_t* layer, void* graphics_ctx)
{
	int32_t dirty = 0;

	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	_ugui_graphics_push_layer_ctx((ugui_graphics_t*) graphics_ctx, bounds);

	if (layer->update != NULL) layer->update(layer, graphics_ctx, layer->ctx);

	for (uint32_t i = 0; i < UGUI_LAYER_MAX_CHILDREN; i++) {
		if (layer->children[i] != NULL) {
			dirty += _ugui_layer_update(layer->children[i], graphics_ctx);
		}
	}

	_ugui_graphics_pop_layer_ctx((ugui_graphics_t*) graphics_ctx, bounds);

	return layer->dirty || (dirty > 0);
}





