
#ifndef UGUI_WINDOW_H
#define UGUI_WINDOW_H

#ifdef __cplusplus
extern "C" {
#endif

#include "layer.h"

/***			Public				***/

typedef struct ugui_window_s* ugui_window_t;

typedef void (*ugui_window_handler_t)(ugui_window_t window);

typedef void (*ugui_window_event_handler_t)(ugui_window_t window, int event);

typedef struct ugui_window_handlers_s {
	ugui_window_handler_t load;
	ugui_window_handler_t unload;
	ugui_window_event_handler_t event;
} ugui_window_handlers_t;

ugui_window_t ugui_window_create();

void ugui_window_destroy(ugui_window_t window);



ugui_layer_t ugui_window_get_base_layer(ugui_window_t window);

void ugui_window_set_window_handlers(ugui_window_t window, ugui_window_handlers_t handlers);

/***			Private				***/

void _ugui_window_put_event(ugui_window_t window, int event);

void _ugui_window_update(ugui_window_t window, void* craphics_ctx);

void _ugui_window_load(ugui_window_t window);

void _ugui_window_unload(ugui_window_t window);

#ifdef __cplusplus
}
#endif

#endif
