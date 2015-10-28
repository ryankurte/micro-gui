
#ifndef UGUI_H
#define UGUI_H

#include <stdint.h>

#include "layer.h"
#include "window.h"
#include "types.h"

#define UGUI_MAX_WINDOW_DEPTH			16

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ugui_s* ugui_t;

ugui_t ugui_create(uint32_t w, uint32_t h);

void ugui_destroy(ugui_t gui);

void ugui_window_stack_push(ugui_t gui, ugui_window_t window);

void ugui_window_stack_pop(ugui_t gui);


#ifdef __cplusplus
}
#endif

#endif
