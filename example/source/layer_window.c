
#include "layer_window.h"

#include "ugui.h"

ugui_window_t *layer_example_window;
ugui_layer_t* quadrant_layers[4];


/***			Internal Functions				***/

static void quadrant_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	ugui_graphics_draw_text(graphics_ctx,
	                        (char*)layer_ctx,
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = 0, .y = 0
	});

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

	ugui_layer_set_dirty(layer);
}

char *layer_names[4] = {
	"top left",
	"top right",
	"bottom left",
	"bottom right"
};

static void main_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
	ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

	int w = bounds->w;
	int h = bounds->h;

	ugui_size_t text_size;
	ugui_font_get_text_size(&font_robotomono_regular_18,
	                        "Layer Demo",
	                        &text_size);

	ugui_graphics_draw_text(graphics_ctx,
	                        "Layer Demo",
	                        &font_robotomono_regular_18,
	(ugui_point_t) {
		.x = w / 2 - text_size.w / 2, .y = h / 4
	});

	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = w / 2, .y = 0
	}, (ugui_point_t) {
		.x = w / 2, .y = h - 1
	});

	ugui_graphics_draw_line(graphics_ctx, (ugui_point_t) {
		.x = 0, .y = h / 2
	}, (ugui_point_t) {
		.x = w - 1, .y = h / 2
	});

	ugui_layer_set_dirty(layer);
}

/***			External Functions				***/

ugui_window_t* layer_window_create(uint32_t w, uint32_t h)
{
	layer_example_window = ugui_window_create(w, h);

	ugui_layer_t* base_layer = ugui_window_get_base_layer(layer_example_window);

	ugui_layer_set_update(base_layer, main_layer_update);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			quadrant_layers[i * 2 + j] = ugui_layer_create((ugui_rect_t) {
				.x = w / 2 * j,
				 .y = h / 2 * i,
				  .w = w / 2,
				   .h = h / 2
			});

			ugui_layer_set_update(quadrant_layers[i * 2 + j], quadrant_layer_update);

			ugui_layer_set_ctx(quadrant_layers[i * 2 + j], (void*)layer_names[i * 2 + j]);

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


