
#include "sprite.h"

#include "types.h"

//TODO: Function depends on b/w or color implementation
uint8_t _ugui_sprite_get_pixel(ugui_sprite_t *sprite, uint16_t x, uint16_t y, ugui_pixel_t* pixel)
{
	if((x < 0) || (x > sprite->w) || (y < 0) || (y > sprite->h)) {
		return 0;
	}

	uint8_t byte = sprite->data[y * sprite->w_bytes + x / 8];
	uint8_t mask = 1 << (7 - (x % 8));

	*pixel = (bool)((byte & mask) != 0);

	return 1;
}
