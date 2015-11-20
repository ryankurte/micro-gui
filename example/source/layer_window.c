
#include "ugui.h"

ugui_window_t *layer_example_window;
ugui_layer_t* quadrant_layers[4];


/***			Internal Functions				***/

static void quadrant_layer_update(ugui_layer_t* layer, void* graphics_ctx)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = 0
	}, (ugui_point_t) {
		.x = w, .y = h
	});

	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = h
	}, (ugui_point_t) {
		.x = w, .y = 0
	});

	uint8_t fake_data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	ugui_graphics_draw_sprite(graphics_ctx, (ugui_sprite_t) {
		.w = 8, .h = 8, .data = (bool*)fake_data
	}, (ugui_point_t) {
		.x = w / 2 - 4, .y = h / 2 - 4
	});

	ugui_layer_set_dirty(layer);
}

/***			External Functions				***/

ugui_window_t* layer_window_create(uint32_t w, uint32_t h)
{
	layer_example_window = ugui_window_create(w, h);

	ugui_layer_t* base_layer = ugui_window_get_base_layer(layer_example_window);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			quadrant_layers[i * 2 + j] = ugui_layer_create((ugui_rect_t) {
				.x = w / 2 * i,
				 .y = h / 2 * j,
				  .w = w / 2,
				   .h = h / 2
			});

			ugui_layer_set_update(quadrant_layers[i * 2 + j], quadrant_layer_update);

			ugui_layer_add_child(base_layer, quadrant_layers[i * 2 + j]);
		}
	}

	return layer_example_window;
}

void layer_window_destroy()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			ugui_layer_destroy(quadrant_layers[i * 2 + j]);
		}
	}

	ugui_window_destroy(layer_example_window);
}


