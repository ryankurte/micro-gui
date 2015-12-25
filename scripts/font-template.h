/**
 * Font header template
 * For use with the ugui python ttf font -> sprite generator
 * See build-font.py
 *
 * Font name: {{name}}
 * Font size: {{size}}
 * Start char: {{start}}
 * End char: {{end}}
 */

#include <stdint.h>

#include "ugui/font.h"

#ifndef FONT_{{NAME}}_{{size}}_H
#define FONT_{{NAME}}_{{size}}_H

font_style_t font_{{name}}_{{size}};

#endif
