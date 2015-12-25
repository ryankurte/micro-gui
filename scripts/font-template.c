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

#include <stdint.h>

#include <stdint.h>

#include "fonts/font_style.h"

{{#chars}}
static const uint8_t font_{{name}}_size_{{size}}_char_{{code}}[] = {  //{{char}}
{{string}}
};
{{/chars}}
