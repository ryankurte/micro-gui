
#include "graphics.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

static int get_octant(ugui_point_t a, ugui_point_t b)
{

}


static void draw_line_internal(ugui_graphics_t graphics, ugui_point_t a, ugui_point_t b)
{
	int deltax = (b.x - a.x);
	int deltay = (b.y - a.y);

	int signx = SIGN(deltax);
	int signy = SIGN(deltay);

	deltax = ABS(deltax);
	deltay = ABS(deltay);

	//b.x += signx;
	//b.y += signy;

	plot(graphics, a.x, a.y);

	int d = 2 * deltay - deltax;

	if (deltax > deltay)
	{
		int y = a.y;

		for (int i = a.x + 1; i < b.x; i++) {
			plot(graphics, i, y);
			d += (2 * deltay);

			if (d > 0) {
				y += 1;
				d -= (2 * deltax);
			}
		}
	} else {
		int x = a.x;

		for (int i = a.y + 1; i < b.y; i++) {
			plot(graphics, x, i);
			d += (2 * deltax);

			if (d > 0) {
				x += 1;
				d -= (2 * deltay);
			}
		}
	}

	/*	accum = deltax >> 1;
		do {
			setCell(x1, y1, 0.4, 0.7, 1.0);

			accum -= dy;
			if (accum < 0)
			{
				accum += dx;
				y1 += sy;
			}

			x1 += sx;
		} while (x1 != x2);
	} else {
		accum = dy >> 1;
		do {
			setCell(x1, y1, 0.4, 0.7, 1.0);

			accum -= dx;
			if (accum < 0)
			{
				accum += dy;
				x1 += sx;
			}

			y1 += sy;
		} while (y1 != y2);
	}
	*/

}

void ugui_graphics_draw_line(ugui_graphics_t graphics, ugui_point_t a, ugui_point_t b)
{

	if (a.x <= b.x) {
		draw_line_internal(graphics, a, b);
	} else {
		draw_line_internal(graphics, b, a);
	}

#if 0
	for (int i = 0; i < rect.h; i++) {
		for (int j = 0; j < rect.w; j++) {

		}
	}
#endif
}

void ugui_graphics_draw_text(ugui_graphics_t graphics, char* text, ugui_font_t font)
{

}

