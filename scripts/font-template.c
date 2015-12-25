/**
 * Font source template
 * For use with the ugui python ttf font -> c font generator
 * See build-font.py
 * 
 * Name: {{name}}
 * Size: {{size}}
 */

#include <stdint.h>

#include <stdint.h>

#include "fonts/font_style.h"

{{#chars}}
static const uint8_t font_{{name}}_size_{{size}}_char_{{code}}[] = { {{string}} };
{{/chars}}
