/**
 * Font source template
 * For use with the ugui python ttf font -> c font generator
 * See build-font.py
 * 
 * Font name: {{name}}
 * Font size: {{size}}
 * Start char: {{start}}
 * End char: {{end}}
 */

#include "ugui/fonts/{{name}}_{{size}}.h"

#include <stdint.h>

#include "ugui/font.h"


static const uint8_t font_{{name}}_{{size}}_map[] = {  
{{#chars}}
// Symbol: {{char}} Code: {{code}} Width: {{width}}
{{string}}
{{/chars}}
};

static uint8_t const font_{{name}}_{{size}}_widths[{{count}}] = 
{
{{#chars}}
{{width}},
{{/chars}}
};

font_style_t font_{{name}}_{{size}} = 
{
    {{count}},    // Glyph count
    {{start}},    // First ascii code
    {{char_width}},    // Glyph width (bytes)
    {{char_height}},    // Glyph height (bytes)
    0,    // Fixed width or 0 if variable
    font_{{name}}_{{size}}_widths,
    font_{{name}}_{{size}}_map
};
