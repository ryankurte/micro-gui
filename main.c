
#include <stdio.h>

#include "ugui.h"

#define GUI_WIDTH	640
#define GUI_HEIGHT	480

int main(int argc, char *argv[])
{
	ugui_t gui = ugui_create(GUI_WIDTH, GUI_HEIGHT);


	ugui_destroy(gui);

    return 0;
}