

#include "ugui/buffer.h"

#include <stdlib.h>

struct ugui_buffer_s {
	uint16_t w;
	uint16_t h;
	uint16_t row_width_bytes;
	uint8_t* data;
};

ugui_buffer_t* _ugui_buffer_create(uint16_t w, uint16_t h, int8_t bits_per_pixel) {
	ugui_buffer_t* buffer = (ugui_buffer_t*)malloc(sizeof(ugui_buffer_t));
	if (buffer == NULL) return NULL;

	buffer->h = h;
	buffer->w = w;

	//Calculate row length in bytes (with padding)
	//TODO: probably need to pad to 32-bit alignment
	//TODO: could allow porch and trailers to streamline DMA to display
	//TODO: prove either of these things are useful before implementing
	int row_width = (w * bits_per_pixel ) / 8;
	buffer->row_width_bytes = row_width + (((w * bits_per_pixel) % 8 > 0) ? 1 : 0);

	int size = buffer->row_width_bytes * h;

	//Allocate pixel memory
	//TODO: this may need to be injected for use with DMA
	buffer->data = (uint8_t*)malloc(size);
	if (buffer->data == NULL) {
		free(buffer);
		return NULL;
	}

	return buffer;
}

uint8_t* _ugui_buffer_get_row(ugui_buffer_t* buffer, uint16_t index)
{
	return buffer->data + buffer->row_width_bytes * index;
}

void _ugui_buffer_set(ugui_buffer_t* buffer, ugui_point_t* point, ugui_pixel_t value) {
	int y = point->y;
	int x = point->x / 8;
	int shift = point->x % 8;

	if (value) {
		buffer->data[buffer->row_width_bytes * y + x] |= (value << shift);
	} else {
		buffer->data[buffer->row_width_bytes * y + x] &= ~(value << shift);
	}
}

void _ugui_buffer_clear(ugui_buffer_t* buffer) {
	for (int16_t i = 0; i < buffer->h; i++) {
		for (int16_t j = 0; j < buffer->row_width_bytes; j++) {
			buffer->data[i * buffer->row_width_bytes + j] = 0;
		}
	}
}

uint8_t* _ugui_buffer_get_data(ugui_buffer_t* buffer) {
	return buffer->data;
}

void _ugui_buffer_destroy(ugui_buffer_t* buffer)
{
	free(buffer->data);

	free(buffer);
}

