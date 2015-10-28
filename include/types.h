
#ifndef UGUI_TYPES_H
#define UGUI_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
