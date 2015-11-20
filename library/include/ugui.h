
#ifndef UGUI_H
#define UGUI_H

#include <stdint.h>
#include <stdbool.h>

#include "layer.h"
#include "window.h"
#include "types.h"
#include "graphics.h"

#define UGUI_MAX_WINDOW_DEPTH			16

#ifdef __cplusplus
extern "C" {
#endif

enum ugui_event_e {
	UGUI_EVT_NONE = 0,
	UGUI_EVT_UP,
	UGUI_EVT_DOWN,
	UGUI_EVT_LEFT,
	UGUI_EVT_RIGHT,
	UGUI_EVT_SELECT,
	UGUI_EVT_BACK
};

typedef struct ugui_s ugui_t;

ugui_t* ugui_create(uint32_t w, uint32_t h);

void ugui_destroy(ugui_t* gui);

void ugui_put_event(ugui_t* gui, uint8_t event);

void ugui_render(ugui_t* gui);

bool* ugui_get_image(ugui_t* gui);

void ugui_window_stack_push(ugui_t* gui, ugui_window_t *window);

void ugui_window_stack_pop(ugui_t* gui);


#ifdef __cplusplus
}
#endif

#endif
