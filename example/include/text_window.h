
#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H

#include "ugui/ugui.h"
#include <stdint.h>

ugui_window_t* text_window_create(uint32_t w, uint32_t h);
void text_window_destroy();

#endif