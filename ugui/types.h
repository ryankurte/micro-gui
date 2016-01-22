
#ifndef UGUI_TYPES_H
#define UGUI_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(UGUI_MODE_COLOR_16BIT)
#error NOT YET SUPPORTED
struct ugui_pixel_s {
	uint8_t r : 5;
	uint8_t g : 6;
	uint8_t b : 5;
} __attribute((packed));

typedef struct ugui_pixel_s ugui_pixel_t;

#elif defined(UGUI_MODE_COLOR_24BIT)

struct ugui_pixel_s {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} __attribute((packed));

typedef struct ugui_pixel_s ugui_pixel_t;

#else

typedef bool ugui_pixel_t;

#endif

typedef struct ugui_point_s {
	uint16_t x;
	uint16_t y;
} ugui_point_t;

typedef struct ugui_size_s {
	uint16_t w;
	uint16_t h;
} ugui_size_t;

typedef struct ugui_rect_s {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
} ugui_rect_t;

typedef struct ugui_sprite_s {
	uint16_t w;
	uint16_t h;
	uint16_t w_bytes;
	uint8_t* data;
} ugui_sprite_t;

#ifdef __cplusplus
}
#endif

#endif
