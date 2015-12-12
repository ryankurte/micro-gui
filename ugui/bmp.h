/**
 * Bitmap generator
 * Generates BMP files from the provided data arrays
 * This is useful for testing of the graphics framework
 */

#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdbool.h>

#include "ugui/types.h"

#ifdef __cplusplus
extern "C" {
#endif

int bmp_create_bw(char* filename, uint32_t w, uint32_t h, uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif
