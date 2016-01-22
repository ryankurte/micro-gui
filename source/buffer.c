

#include "ugui/buffer.h"

#include <stdlib.h>

struct ugui_buffer_s {
	uint16_t w;			//!< Buffer width in pixels
	uint16_t h;			//!< Buffer height in pixels

	uint16_t row_width_bytes;	//!< Width of a buffer row in bytes

	uint8_t porch;		//!< Padding before each row in the buffer
	uint8_t trailer;	//!< Padding after each row in the buffer

	uint8_t* data;		//!< Storage of pixel data
};

ugui_buffer_t* _ugui_buffer_create(uint16_t w, uint16_t h, uint16_t porch, uint16_t trailer) {
	ugui_buffer_t* buffer = (ugui_buffer_t*)malloc(sizeof(ugui_buffer_t));
	if (buffer == NULL) return NULL;

	buffer->h = h;
	buffer->w = w;

	buffer->porch = porch;
	buffer->trailer = trailer;

	//Calculate row length in bytes (with padding)
	//TODO: probably need to pad to 32-bit alignment
	//TODO: could allow porch and trailers to streamline DMA to display
	//TODO: prove either of these things are useful before implementing
#ifdef UGUI_COLOUR
	buffer->row_width_bytes = (w * sizeof(ugui_pixel_t)) + porch + trailer;
	int size = buffer->row_width_bytes * h;

#else
	int row_width = w / 8 + porch + trailer;
	buffer->row_width_bytes = row_width + ((w % 8 > 0) ? 1 : 0);

	int size = buffer->row_width_bytes * h;
#endif

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
	return buffer->data + buffer->row_width_bytes * index + buffer->porch;
}

void _ugui_buffer_set(ugui_buffer_t* buffer, ugui_point_t* point, ugui_pixel_t value) {
#ifdef UGUI_COLOUR
	int y = point->y;
	int x = point->x;

	int index = buffer->row_width_bytes * y
	            + x * sizeof(ugui_pixel_t) +
	            buffer->porch +
	            i;
	memcpy(buffer->data[index],
	       &value,
	       sizeof(ugui_pixel_t));
#else
	int y = point->y;
	int x = point->x / 8;
	int shift = point->x % 8;

	if (value) {
		buffer->data[buffer->row_width_bytes * y + x] |= (value << shift);
	} else {
		buffer->data[buffer->row_width_bytes * y + x] &= ~(value << shift);
	}

#endif
}

void _ugui_buffer_get(ugui_buffer_t* buffer, ugui_point_t* point, ugui_pixel_t* value) {
#ifdef UGUI_COLOUR
	int y = point->y;
	int x = point->x;

	int index = buffer->row_width_bytes * y
	            + x * sizeof(ugui_pixel_t) +
	            buffer->porch +
	            i;
	memcpy(&value,
	       buffer->data[index],
	       sizeof(ugui_pixel_t));
#else
	int y = point->y;
	int x = point->x / 8;
	int shift = point->x % 8;

	*value = ((buffer->data[buffer->row_width_bytes * y + x] & (1 << shift)) != 0);
#endif
}

void _ugui_buffer_inverse(ugui_buffer_t* buffer, ugui_point_t* point) {
#ifdef UGUI_COLOUR
	int x = point->x;
	int y = point->y;

	for (int i = 0; i < sizeof(ugui_pixel_t); i++) {
		int index = buffer->row_width_bytes * y
		            + x * sizeof(ugui_pixel_t) +
		            buffer->porch +
		            i;
		uint8_t* ptr = buffer->data[index];
		*ptr ^= *ptr;
	}
#else
	int y = point->y;
	int x = point->x / 8;
	int shift = point->x % 8;

	buffer->data[buffer->row_width_bytes * y + x] ^= (1 << shift);
#endif
}

void _ugui_buffer_clear(ugui_buffer_t* buffer) {
	for (int i = 0; i < buffer->h; i++) {
		for (int j = 0; j < buffer->row_width_bytes; j++) {
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

