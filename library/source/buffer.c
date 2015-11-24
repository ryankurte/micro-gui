

#include "buffer.h"

#include <stdlib.h>

struct ugui_buffer_s {
	uint16_t w;
	uint16_t h;
	uint16_t row_width_bytes;
	uint8_t* data;
};

ugui_buffer_t* _ugui_buffer_create(uint16_t w, uint16_t h, int8_t bits_per_pixel) {
	ugui_buffer_t* buffer = (uint8_t*)malloc(sizeof(buffer));
	if(buffer == NULL) return NULL;

	buffer->h = h;
	buffer->w = w;

	//Calculate row length in bytes (with padding)
	int row_width = (w * bits_per_pixel ) / 8;
	buffer->row_width_bytes = row_width + (((w * bits_per_pixel) % 8 > 0) ? 1 : 0);

	int size = buffer->row_width_bytes * h;

	buffer->data = (uint8_t*)malloc(size);
	if(buffer->data == NULL) {
		free(buffer);
		return NULL;
	}

	return buffer;
}

uint8_t* _ugui_buffer_get_row(ugui_buffer_t* buffer, uint16_t index)
{
	return buffer->data + buffer->row_width_bytes * index;
}

void _ugui_buffer_destroy(ugui_buffer_t* buffer) 
{
	free(buffer->data);

	free(buffer);
}

