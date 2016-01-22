
#include "ugui/ugui.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "ugui/graphics.h"
#include "ugui/buffer.h"

struct ugui_s {
	uint32_t w;
	uint32_t h;
	ugui_buffer_t* buffer;
	ugui_graphics_t* graphics;
	ugui_window_t *windows[UGUI_MAX_WINDOW_DEPTH];
	uint32_t window_index;
};

ugui_t* ugui_create(uint32_t w, uint32_t h)
{
	ugui_t* gui = malloc(sizeof(struct ugui_s));

	gui->buffer = _ugui_buffer_create(w, h, 0, 0);

	gui->w = w;
	gui->h = h;
	gui->window_index = 0;

	for (int i = 0; i < UGUI_MAX_WINDOW_DEPTH; i++) {
		gui->windows[i] = NULL;
	}

	gui->graphics = ugui_graphics_create(w, h, gui->buffer);

	return gui;
}

void ugui_destroy(ugui_t* gui)
{
	free(gui->buffer);

	free(gui);
}

uint8_t* ugui_get_image(ugui_t* gui)
{
	return _ugui_buffer_get_data(gui->buffer);
}

void ugui_put_event(ugui_t* gui, uint8_t event)
{
	//Bypass for null events
	if(event == UGUI_EVT_NONE) {
		return;
	}
	//Pass event to active window handler
	ugui_window_t *current = gui->windows[gui->window_index - 1];
	_ugui_window_put_event(current, event);
}

void ugui_render(ugui_t* gui)
{
	//TODO: render only if dirty..?
	//TODO: Think about how layers work & offset rendering in update calls
	ugui_graphics_clear(gui->graphics);
	ugui_window_t *current = gui->windows[gui->window_index - 1];
	_ugui_window_update(current, gui->graphics);
}

void ugui_window_stack_push(ugui_t* gui, ugui_window_t *window)
{
	//Unload last window
	if (gui->window_index > 0) {
		ugui_window_t *last = gui->windows[gui->window_index - 1];
		_ugui_window_unload(last);
	}

	//Update pointer
	gui->windows[gui->window_index] = window;
	gui->window_index ++;

	//Load new window
	_ugui_window_load(window);
}

void ugui_window_stack_pop(ugui_t* gui)
{
	//Unload last window
	if (gui->window_index > 0) {
		ugui_window_t *last = gui->windows[gui->window_index - 1];
		_ugui_window_unload(last);

		//Update pointer
		gui->window_index --;
		ugui_window_t *next = gui->windows[gui->window_index];

		//Load new window
		_ugui_window_load(next);
	}
}

