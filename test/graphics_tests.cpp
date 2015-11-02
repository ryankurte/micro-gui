
void line_test() {
	
	//Horizontal
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = 0, .y = h / 2
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Vertical
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = w / 2, .y = 0
	}, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	});

	//Diagonal gentle down
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = 0, .y = 0
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Diagonal gentle up
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = 0, .y = h - 1
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Diagonal sharp down
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = 0, .y = 0
	}, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	});

	//Diagonal sharp up
	ugui_graphics_draw_line(gui->graphics, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	}, (ugui_point_t) {
		.x = w - 1, .y = 0
	});
}

