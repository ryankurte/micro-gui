
#include "ugui.h"

#include <stdlib.h>

struct ugui_s {
	uint32_t w;
	uint32_t h;
	uint32_t* buffer;
	ugui_window_t windows[UGUI_MAX_WINDOW_DEPTH];
	uint32_t window_index;
};

ugui_t ugui_create(uint32_t w, uint32_t h)
{
	ugui_t gui = malloc(sizeof(struct ugui_s));

	gui->buffer = malloc(w * h / sizeof(uint8_t) + 1);

	gui->w = w;
	gui->h = h;
	gui->window_index = 0;

	for (int i = 0; i < UGUI_MAX_WINDOW_DEPTH; i++) {
		gui->windows[i] = NULL;
	}

	return gui;
}

void ugui_destroy(ugui_t gui)
{
	free(gui->buffer);

	free(gui);
}

void ugui_window_stack_push(ugui_t gui, ugui_window_t window)
{
	//Unload last window
	ugui_window_t last = gui->windows[gui->window_index - 1];
	ugui_window_unload(last);
	//Update pointer
	gui->window_index ++;
	gui->windows[gui->window_index - 1] = window;
	//Load new window
	ugui_window_load(window);
}

void ugui_window_stack_pop(ugui_t gui)
{
	//Unload last window
	ugui_window_t last = gui->windows[gui->window_index - 1];
	ugui_window_unload(last);
	//Update pointer
	gui->window_index --;
	ugui_window_t next = gui->windows[gui->window_index - 1];
	//Load new window
	ugui_window_load(next);
}
