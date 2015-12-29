
#include "ugui/ugui_sdl.h"

#include <stdint.h>


#include "ugui/ugui.h"
#include "SDL2/SDL.h"

struct ugui_sdl_s {
	SDL_Window *win;
	SDL_Renderer *ren;
};

ugui_sdl_t* ugui_sdl_init(char* title, int width, int height) {

	ugui_sdl_t* sdl_ctx = (ugui_sdl_t*)malloc(sizeof(ugui_sdl_t));

	SDL_Init(SDL_INIT_EVERYTHING);

	sdl_ctx->win = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_SHOWN);
	sdl_ctx->ren = SDL_CreateRenderer(sdl_ctx->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return sdl_ctx;
}

int ugui_sdl_get_event(ugui_sdl_t* sdl_ctx) {
	//Handle SDL events
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return UGUI_EVT_EXIT;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				return UGUI_EVT_UP;
			case SDLK_DOWN:
				return UGUI_EVT_DOWN;
			case SDLK_LEFT:
				return UGUI_EVT_LEFT;
			case SDLK_RIGHT:
				return UGUI_EVT_RIGHT;
			case SDLK_ESCAPE:
			case SDLK_q:
				return UGUI_EVT_EXIT;
			}
		}
	}
	return UGUI_EVT_NONE;
}

void ugui_sdl_render_bmp(ugui_sdl_t* sdl_ctx, char* name) {
	SDL_Surface *bmp = SDL_LoadBMP(name);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(sdl_ctx->ren, bmp);

	SDL_RenderClear(sdl_ctx->ren);
	SDL_RenderCopy(sdl_ctx->ren, tex, NULL, NULL);
	SDL_RenderPresent(sdl_ctx->ren);

	SDL_DestroyTexture(tex);

	SDL_FreeSurface(bmp);
}

void ugui_sdl_close(ugui_sdl_t* sdl_ctx) {
	SDL_DestroyRenderer(sdl_ctx->ren);
	SDL_DestroyWindow(sdl_ctx->win);

	SDL_Quit();

	free(sdl_ctx);
}
