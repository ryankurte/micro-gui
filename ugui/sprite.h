
#ifndef UGUI_SPRITE_H
#define UGUI_SPRITE_H

#include <stdint.h>
#include <stdbool.h>

#include "ugui/types.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t _ugui_sprite_get_pixel(ugui_sprite_t *sprite, uint16_t x, uint16_t y, ugui_pixel_t* pixel);

#ifdef __cplusplus
}
#endif

#endif
