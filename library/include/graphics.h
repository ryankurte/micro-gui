
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/***			Public				***/

typedef struct ugui_graphics_s * ugui_graphics_t;

ugui_graphics_t ugui_graphics_create(uint32_t w, uint32_t h, bool* buffer);

void ugui_graphics_destroy(ugui_graphics_t graphics);

void ugui_graphics_draw_line(ugui_graphics_t graphics, ugui_point_t a, ugui_point_t b);

void ugui_graphics_draw_rect(ugui_graphics_t graphics, ugui_point_t a, ugui_size_t size);

void ugui_graphics_fill_rect(ugui_graphics_t graphics, ugui_point_t a, ugui_size_t size);

void ugui_graphics_draw_ellipse(ugui_graphics_t graphics, ugui_rect_t rect);

void ugui_graphics_draw_sprite(ugui_graphics_t graphics, ugui_sprite_t sprite, ugui_point_t point);

void ugui_graphics_draw_text(ugui_graphics_t graphics, char* text, ugui_font_t font, ugui_point_t point);

void ugui_graphics_clear(ugui_graphics_t graphics);


/***			Private				***/

void _ugui_graphics_push_layer_ctx(ugui_graphics_t graphics, ugui_rect_t *bounds);

void _ugui_graphics_pop_layer_ctx(ugui_graphics_t graphics, ugui_rect_t *bounds);

#ifdef __cplusplus
}
#endif

#endif
