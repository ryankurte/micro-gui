
#ifndef LINE_WINDOW_H
#define LINE_WINDOW_H

#include "ugui.h"
#include <stdint.h>

ugui_window_t line_window_create(uint32_t w, uint32_t h);
void line_window_destroy();

#endif