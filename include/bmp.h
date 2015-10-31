
#ifndef UGUI_LAYER_H
#define UGUI_LAYER_H

#include <stdint.h>
#include <stdbool.h>

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int bmp_create(char* filename, uint32_t w, uint32_t h, bool* data);

#ifdef __cplusplus
}
#endif

#endif
