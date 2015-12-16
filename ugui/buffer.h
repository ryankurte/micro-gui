
#ifndef UGUI_BUFFER_H
#define UGUI_BUFFER_H

#include <stdint.h>

#include "ugui/types.h"

typedef struct ugui_buffer_s ugui_buffer_t;

ugui_buffer_t* _ugui_buffer_create(uint16_t w, uint16_t h, int8_t bits_per_pixel);

void _ugui_buffer_set(ugui_buffer_t* buffer, ugui_point_t* point, ugui_pixel_t value);

void _ugui_buffer_get(ugui_buffer_t* buffer, ugui_point_t* point, ugui_pixel_t* value);

void _ugui_buffer_clear(ugui_buffer_t* buffer);

uint8_t* _ugui_buffer_get_data(ugui_buffer_t* buffer);

void _ugui_buffer_destroy(ugui_buffer_t* buffer);

#endif
