
#include "ugui.h"

#include <stdlib.h>

struct ugui_s {
	uint32_t w;
	uint32_t h;
	uint32_t* buffer;
};

ugui_t ugui_create(uint32_t w, uint32_t h)
{
	ugui_t gui = malloc(sizeof(struct ugui_s));

	gui->buffer = malloc(w * h / sizeof(uint8_t) + 1);

	gui->w = w;
	gui->h = h;

	return gui;
}

void ugui_destroy(ugui_t gui)
{
	free(gui->buffer);

	free(gui);
}

