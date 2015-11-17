
#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL.h"

#include "ugui.h"
#include "bmp.h"
#include "line_window.h"
#include "circle_window.h"
#include "layer_window.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

ugui_t gui;
ugui_window_t line_test_window;
ugui_window_t circle_test_window;
ugui_window_t layer_test_window;
int running;

int get_input_event() {
	int event = UGUI_EVT_NONE;
	int input = getchar();
	switch (input) {
	case 'a':
		event = UGUI_EVT_LEFT;
		break;
	case 'd':
		event = UGUI_EVT_RIGHT;
		break;
	case 'w':
		event = UGUI_EVT_UP;
		break;
	case 's':
		event = UGUI_EVT_DOWN;
		break;
	case 'e':
		event = UGUI_EVT_SELECT;
		break;
	case 'q':
		event = UGUI_EVT_BACK;
		break;
	}

	return event;
}

void handle_event(ugui_window_t window, int event)
{
	if (event == UGUI_EVT_RIGHT) {
		ugui_window_stack_pop(gui);
		ugui_window_stack_push(gui, circle_test_window);
	} else if (event == UGUI_EVT_LEFT) {
		ugui_window_stack_pop(gui);
		ugui_window_stack_push(gui, line_test_window);
	} else if (event == UGUI_EVT_UP) {
		ugui_window_stack_pop(gui);
		ugui_window_stack_push(gui, layer_test_window);
	} else if (event == UGUI_EVT_BACK) {
		running = 0;
	}
}

int main(int argc, char *argv[])
{
	SDL_Init( SDL_INIT_EVERYTHING );

	printf("\r\n------------------------------------\r\n");
	printf("micro-gui (ugui) example application\r\n");
	printf("Output will appear (while running) in ./test.bmp\r\n");
	//TODO: notes about SDL, make SDL rendering optional arg
	printf("Use wasd to for directional navigation, q for back, and e for select\r\n");
	printf("Note that you will need to press enter following each command\r\n");

	SDL_Window *win = SDL_CreateWindow("micro-gui example", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);
	running = 1;

	line_test_window = line_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(line_test_window, handle_event);

	circle_test_window = circle_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(circle_test_window, handle_event);

	layer_test_window = layer_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(layer_test_window, handle_event);

	ugui_window_stack_push(gui, line_test_window);

	ugui_render(gui);

	while (running > 0) {
		//int event = get_input_event();
		//ugui_put_event(gui, event);

		//Handle SDL events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					ugui_put_event(gui, UGUI_EVT_UP);
					break;
				case SDLK_DOWN:
					ugui_put_event(gui, UGUI_EVT_DOWN);
					break;
				case SDLK_LEFT:
					ugui_put_event(gui, UGUI_EVT_LEFT);
					break;
				case SDLK_RIGHT:
					ugui_put_event(gui, UGUI_EVT_RIGHT);
					break;
				case SDLK_ESCAPE:
				case SDLK_q:
					running = 0;
					break;
				}
			}
		}

		ugui_render(gui);

		bool *img = ugui_get_image(gui);

		bmp_create("test.bmp", GUI_WIDTH, GUI_HEIGHT, (bool*)img);

		SDL_Surface *bmp = SDL_LoadBMP("test.bmp");
		SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);

		SDL_DestroyTexture(tex);

		SDL_FreeSurface(bmp);

		usleep(1000);
	}

	ugui_destroy(gui);

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();

	return 0;
}

