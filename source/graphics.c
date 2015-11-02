
#include "graphics.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

#define ABS(x)	(x < 0 ? -x : x)
#define SIGN(x)	(x < 0 ? -1 : (x > 0 ? 1 : 0))

struct ugui_graphics_s {
	uint32_t w;
	uint32_t h;
	bool* buffer;
};

ugui_graphics_t ugui_graphics_create(uint32_t w, uint32_t h, bool* buffer)
{
	ugui_graphics_t graphics = malloc(sizeof(struct ugui_graphics_s));

	graphics->w = w;
	graphics->h = h;
	graphics->buffer = buffer;

	return graphics;
}

void ugui_graphics_destroy(ugui_graphics_t graphics)
{
	free(graphics);
}

static void plot(ugui_graphics_t graphics, uint32_t x, uint32_t y)
{
	if ((x < graphics->w) && (y < graphics->h)) {
		graphics->buffer[y * graphics->w + x] = 1;
	}
}

void ugui_graphics_clear(ugui_graphics_t graphics)
{
	for (int i = 0; i < (graphics->h * graphics->w); i++) {
		graphics->buffer[i] = 0;
	}
}

void ugui_graphics_draw_line(ugui_graphics_t graphics, ugui_point_t a, ugui_point_t b)
{
	//Bresenham's line algorithm (https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm), implementation from:
	//https://www.opengl.org/discussion_boards/showthread.php/168761-Drawing-Line-Bresenhem-midpoint-algorithm

	assert((a.x >= 0) && (a.x < graphics->w));
	assert((a.y >= 0) && (a.y < graphics->h));
	assert((b.x >= 0) && (b.x < graphics->w));
	assert((b.y >= 0) && (b.y < graphics->h));

	int deltax = (b.x - a.x);
	int deltay = (b.y - a.y);

	int signx = SIGN(deltax);
	int signy = SIGN(deltay);

	deltax = ABS(deltax);
	deltay = ABS(deltay);

	b.x += signx;
	b.y += signy;

	plot(graphics, a.x, a.y);

	int d = 2 * deltay - deltax;

	if (deltax > deltay) {

		int accum = deltax / 2;
		do {
			plot(graphics, a.x, a.y);
			accum -= deltay;
			if (accum < 0) {
				accum += deltax;
				a.y += signy;
			}

			a.x += signx;

		} while (a.x != b.x);

	} else {
		int accum = deltay >> 1;
		do {
			plot(graphics, a.x, a.y);

			accum -= deltax;
			if (accum < 0)
			{
				accum += deltay;
				a.x += signx;
			}

			a.y += signy;
		} while (a.y != b.y);

	}
}


void ugui_graphics_draw_text(ugui_graphics_t graphics, char* text, ugui_font_t font)
{

}

