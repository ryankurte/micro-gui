
#ifndef UGUI_LAYER_H
#define UGUI_LAYER_H

#include <stdint.h>

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ugui_layer_s* ugui_layer_t;

typedef void (*ugui_layer_update_t)(ugui_layer_t *layer, void *gctx);

ugui_layer_t ugui_layer_create(ugui_rect_t bounds);

void ugui_layer_destroy(ugui_layer_t layer);

ugui_rect_t* ugui_layer_get_bounds(ugui_layer_t layer);

void ugui_layer_add_child(ugui_layer_t layer, ugui_layer_t child);

void ugui_layer_set_update(ugui_layer_t layer, ugui_layer_update_t update);

void ugui_layer_set_dirty(ugui_layer_t layer);


#ifdef __cplusplus
}
#endif

#endif
