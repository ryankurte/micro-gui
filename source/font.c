

#include "ugui/font.h"

#include <string.h>

#include "ugui/types.h"

int ugui_font_get_text_size(font_style_t *font, char *c, ugui_size_t* size) {
	uint16_t len = strlen(c);
	
	size->h = font->glyph_height;
	size->w = 0;

	for(uint16_t i=0; i<len; i++) {
		uint16_t index = c[i] - font->first_ascii_code;
		size->w += font->glyph_width[index];
	}

	return 0;
}

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

