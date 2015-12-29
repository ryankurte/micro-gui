/**
 * Bitmap generator
 * Generates BMP files from the provided data arrays
 * This is useful for testing of the graphics framework
 */

#ifndef UGUI_SDL_H
#define UGUI_SDL_H

#include <stdint.h>
#include <stdbool.h>

#include "ugui/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ugui_sdl_s ugui_sdl_t;

ugui_sdl_t* ugui_sdl_init(char* title, int width, int height);
int ugui_sdl_get_event(ugui_sdl_t* sdl_ctx);
void ugui_sdl_render_bmp(ugui_sdl_t* sdl_ctx, char* name);
void ugui_sdl_close(ugui_sdl_t* sdl_ctx);

#ifdef __cplusplus
}
#endif

#endif


