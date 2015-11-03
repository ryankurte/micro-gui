
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
			if (accum < 0) {
				accum += deltay;
				a.x += signx;
			}
			a.y += signy;

		} while (a.y != b.y);

	}
}

void ugui_graphics_draw_ellipse(ugui_graphics_t graphics, ugui_rect_t rect)
{
	//Implementation also from:
	//https://www.opengl.org/discussion_boards/showthread.php/168761-Drawing-Line-Bresenhem-midpoint-algorithm

	int		a, b;
	int		x, y, a2, b2, S, T;
	int		two_a2, two_b2;
	int		four_a2, four_b2;
	int		temp;

	int left = rect.x;
	int right = rect.x + rect.w;
	int top = rect.y;
	int bottom = rect.y + rect.h;

	//Flip logic, should not be required as rect should be ordered already.
	if (right < left) {
		temp = left;
		left = right;
		right = temp;
	}
	if (bottom < top) {
		temp = top;
		top = bottom;
		bottom = temp;
	}

	a = (right - left + 1) / 2;
	b = (bottom - top + 1) / 2;

	if (!a && !b) {
		plot(graphics, left, top); // Draw a single pixel
		return;
	}

	if (!b) {
		ugui_graphics_draw_line(graphics,
		(ugui_point_t) {.y = top, .x = left},
		(ugui_point_t) {.y = top, .x = right}); // Draw a horizontal line
		return;
	}

	if (!a) {
		ugui_graphics_draw_line(graphics,
		(ugui_point_t) {.y = left, .x = top},
		(ugui_point_t) {.y = left, .x = bottom}); // Draw a vertical line
		return;
	}

	a2 = a * a;
	b2 = b * b;
	two_a2 = a2 << 1;
	two_b2 = b2 << 1;
	four_a2 = a2 << 2;
	four_b2 = b2 << 2;
	x = 0;
	y = b;
	S = a2 * (1 - (b << 1)) + two_b2;
	T = b2 - two_a2 * ((b << 1) - 1);

	plot(graphics, right + x - a, bottom + y - b);
	plot(graphics, left - x + a, bottom + y - b);
	plot(graphics, left - x + a, top - y + b);
	plot(graphics, right + x - a, top - y + b);

	do {
		if (S < 0) {
			S += two_b2 * ((x << 1) + 3);
			T += four_b2 * (x + 1);
			x++;
		} else if (T < 0) {
			S += two_b2 * ((x << 1) + 3) - four_a2 * (y - 1);
			T += four_b2 * (x + 1) - two_a2 * ((y << 1) - 3);
			x++;
			y--;
		} else {
			S -= four_a2 * (y - 1);
			T -= two_a2 * ((y << 1) - 3);
			y--;
		}
		plot(graphics, right + x - a, bottom + y - b);
		plot(graphics, left - x + a, bottom + y - b);
		plot(graphics, left - x + a, top - y + b);
		plot(graphics, right + x - a, top - y + b);
	} while (y > 0);
}

void ugui_graphics_draw_text(ugui_graphics_t graphics, char* text, ugui_font_t font)
{

}

