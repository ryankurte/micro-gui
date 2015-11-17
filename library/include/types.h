
#ifndef UGUI_TYPES_H
#define UGUI_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#include "fonts/font_style.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef bool ugui_pixel_t;

typedef struct ugui_point_s {
	uint32_t x;
	uint32_t y;
} ugui_point_t;

typedef struct ugui_rect_s {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
} ugui_rect_t;

typedef struct ugui_sprite_s {
	uint32_t w;
	uint32_t h;
	ugui_pixel_t* data;
} ugui_sprite_t;

typedef struct ugui_font_s {

} ugui_font_t;

#ifdef __cplusplus
}
#endif

#endif
