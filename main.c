
#include <stdio.h>
#include <stdbool.h>

#include "ugui.h"
#include "bmp.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

int main(int argc, char *argv[])
{
	ugui_t gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);
	int running = 1;

	while(running > 0) {
		bool *img = ugui_get_image(gui);

		bmp_create("test.bmp", GUI_WIDTH, GUI_HEIGHT, (bool*)img);
	}

	ugui_destroy(gui);

	return 0;
}