
#ifndef CIRCLE_WINDOW_H
#define CIRCLE_WINDOW_H

#include "ugui.h"
#include <stdint.h>

ugui_window_t* circle_window_create(uint32_t w, uint32_t h);
void circle_window_destroy();

#endif