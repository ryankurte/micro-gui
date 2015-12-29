
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "ugui/ugui_sdl.h"

#include "ugui/ugui.h"
#include "ugui/bmp.h"

#include "menu_window.h"
#include "line_window.h"
#include "circle_window.h"
#include "layer_window.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

ugui_t* gui;
ugui_window_t* line_test_window;
ugui_window_t* circle_test_window;
ugui_window_t* layer_test_window;
ugui_window_t* menu_test_window;
int running;

int get_input_event()
{
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

void handle_event(ugui_window_t* window, int event)
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

#ifdef USE_SDL2
	printf("\r\n------------------------------------\r\n");
	printf("micro-gui (ugui) example application\r\n");
	printf("Output will appear in an SDL window and real time in ./test.bmp\r\n");
	printf("Use arrow keys for directional navigation\r\n");

#else
printf("\r\n------------------------------------\r\n");
	printf("micro-gui (ugui) example application\r\n");
	printf("Output will appear (while running) in ./test.bmp\r\n");
	printf("You may need to refresh this image manually.\r\n");
	printf("Alternately, compile without -DNO_SDL2 to enable SDL2 based rendering\r\n");
	printf("Use wasd to for directional navigation, q for back, and e for select\r\n");
	printf("Note that you will need to press enter following each command\r\n");
#endif

#ifdef USE_SDL2
	ugui_sdl_t *sdl_ctx = ugui_sdl_init("micro-gui example", GUI_WIDTH, GUI_HEIGHT);
#endif

	gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);
	running = 1;

	menu_test_window = menu_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(menu_test_window, handle_event);

	line_test_window = line_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(line_test_window, handle_event);

	circle_test_window = circle_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(circle_test_window, handle_event);

	layer_test_window = layer_window_create(GUI_WIDTH, GUI_HEIGHT);
	ugui_window_set_event_handler(layer_test_window, handle_event);

	ugui_window_stack_push(gui, menu_test_window);

	ugui_render(gui);

	while (running > 0) {

		//Process input events
#ifdef USE_SDL2
		int event = ugui_sdl_get_event(sdl_ctx);
#else
		int event = get_input_event();
#endif
		if (event == UGUI_EVT_EXIT) {
			break;
		}

		ugui_put_event(gui, event);

		ugui_render(gui);

		uint8_t *img = ugui_get_image(gui);

		bmp_create_bw("test.bmp", GUI_WIDTH, GUI_HEIGHT, img);

#ifdef USE_SDL2
		ugui_sdl_render_bmp(sdl_ctx, "test.bmp");
#endif

		usleep(1000);
	}

	ugui_destroy(gui);

#ifdef USE_SDL2
	ugui_sdl_close(sdl_ctx);
#endif

	return 0;
}

