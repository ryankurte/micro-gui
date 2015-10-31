
#include <stdio.h>
#include <stdbool.h>

#include "ugui.h"
#include "bmp.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

int main(int argc, char *argv[])
{
	ugui_t gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);

	bool img[480][640];

	for (int i = 0; i < 480; i++) {
		for (int j = 0; j < 640; j++) {
			if(i % 2 == 0) {
				img[i][j] = 1;
			} else {
				img[i][j] = 0;
			}
		}
	}

	bmp_create("test.bmp", 640, 480, img);

	ugui_destroy(gui);

	return 0;
}