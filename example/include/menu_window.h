
#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include "ugui.h"
#include <stdint.h>

ugui_window_t* menu_window_create(uint32_t w, uint32_t h);
void menu_window_destroy();

#endif