
#ifndef UGUI_TYPES_H
#define UGUI_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ugui_point_s {
	int32_t x;
	int32_t y;
} ugui_point_t;

typedef struct ugui_rect_s {
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
} ugui_rect_t;

#ifdef __cplusplus
}
#endif

#endif
