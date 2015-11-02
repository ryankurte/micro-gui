
#ifndef UGUI_CANVAS_LAYER_H
#define UGUI_CANVAS_LAYER_H

#include <stdint.h>

#include "layer.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ugui_canvas_layer_s* ugui_canvas_layer_t;

ugui_canvas_layer_t ugui_canvas_layer_create(ugui_rect_t bounds);

void ugui_canvas_layer_destroy(ugui_canvas_layer_t layer);


#ifdef __cplusplus
}
#endif

#endif
