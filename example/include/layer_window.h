
#ifndef LAYER_WINDOW_H
#define LAYER_WINDOW_H

#include "ugui/ugui.h"
#include <stdint.h>

ugui_window_t *layer_window_create(uint32_t w, uint32_t h);
void layer_window_destroy();

#endif