
#include <stdio.h>
#include <stdbool.h>

#include "ugui.h"
#include "bmp.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

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

int main(int argc, char *argv[])
{
	ugui_t gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);
	int running = 1;

	while (running > 0) {

		int event = get_input_event();

		ugui_put_event(gui, event);

		ugui_render(gui);

		bool *img = ugui_get_image(gui);

		bmp_create("test.bmp", GUI_WIDTH, GUI_HEIGHT, (bool*)img);
	}

	ugui_destroy(gui);

	return 0;
}