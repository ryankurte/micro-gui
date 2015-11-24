
#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <stdint.h>

#include "types.h"

typedef struct ugui_buffer_s ugui_buffer_t;

ugui_buffer_t* _ugui_buffer_create(uint16_t w, uint16_t h, int8_t bits_per_pixel);

void _ugui_buffer_destroy(ugui_buffer_t* buffer);

#endif
