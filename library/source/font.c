

#include "font.h"

#include "types.h"

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

