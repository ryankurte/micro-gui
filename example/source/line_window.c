
#include "ugui.h"

#include "font.h"

ugui_window_t *line_window;
ugui_layer_t* line_layer;


/***			Internal Functions				***/

static void line_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	//Horizontal
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = h / 2
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Vertical
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = w / 2, .y = 0
	}, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	});

	//Diagonal gentle down
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = 0
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Diagonal gentle up
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = h - 1
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	//Diagonal sharp down
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = 0
	}, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	});

	//Diagonal sharp up
	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	}, (ugui_point_t) {
		.x = w - 1, .y = 0
	});

	ugui_graphics_draw_text(graphics_ctx,
	                        "test",
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = w / 2, .y = h / 2
	});

	ugui_layer_set_dirty(layer);
}

/***			External Functions				***/

ugui_window_t *line_window_create(uint32_t w, uint32_t h)
{
	line_window = ugui_window_create(w, h);

	line_layer = ugui_layer_create((ugui_rect_t) {.x = 0, .y = 0, .w = w, .h = h});

	ugui_layer_t* base_layer = ugui_window_get_base_layer(line_window);

	ugui_layer_set_update(line_layer, line_layer_update);

	ugui_layer_add_child(base_layer, line_layer);

	return line_window;
}

void line_window_destroy()
{
	ugui_layer_destroy(line_layer);

	ugui_window_destroy(line_window);
}


