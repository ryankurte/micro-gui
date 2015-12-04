

#include "font.h"

#include "types.h"

uint8_t test_arr[] = {
	    // ASCII: 122, char width: 9
    0x00, 0x00,  // ---------.......
    0x00, 0x00,  // ---------.......
    0x00, 0x00,  // ---------.......
    0x00, 0x00,  // ---------.......
    0x7f, 0x00,  // -OOOOOOO-.......
    0x02, 0x00,  // ------O--.......
    0x04, 0x00,  // -----O---.......
    0x0c, 0x00,  // ----OO---.......
    0x18, 0x00,  // ---OO----.......
    0x30, 0x00,  // --OO-----.......
    0x20, 0x00,  // --O------.......
    0x7f, 0x00,  // -OOOOOOO-.......
    0x00, 0x00,  // ---------.......
    0x00, 0x00,  // ---------.......
    0x00, 0x00,  // ---------.......
};

int _ugui_font_get_glyph(font_style_t *font, char c, ugui_sprite_t* glyph) 
{
	//Calculate font index
	uint16_t index = c - font->first_ascii_code;

	//Check index is within bounds for the style
	if(index >= font->glyph_count) {
		return 0;
	}

	//Calculate character offset in memory
	//TODO: either make this more efficient or remove and use only fixed width
	uint16_t offset = index * font->glyph_height * font->glyph_width_bytes;

	glyph->w_bytes = font->glyph_width_bytes;
	glyph->h = font->glyph_height;
	glyph->w = font->glyph_width[index];
	glyph->data = font->glyph_bitmaps + font->glyph_height * font->glyph_width_bytes * index;

	return 1;
}

//Function depends on b/w or color implementation
//Should not be here
uint8_t _ugui_glyph_get_pixel(ugui_sprite_t *sprite, uint16_t x, uint16_t y, ugui_pixel_t* pixel)
{
	if((x < 0) || (x > sprite->w) || (y < 0) || (y > sprite->h)) {
		return 0;
	}

	uint8_t byte = sprite->data[y * sprite->w_bytes + x / 8];
	uint8_t mask = 1 << (x % 8);

	*pixel = (bool)((byte & mask) != 0);

	return 1;
}

