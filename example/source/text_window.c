
#include "text_window.h"

#include "ugui/ugui.h"
#include "ugui/font.h"

#include "ugui/widgets/text_widget.h"

ugui_window_t *text_window;
ugui_text_widget_t* text_widget;

const char* sample_one = "This is a sample text area, with a long string that will be \
automatically wrapped to fit the defined area. This determines the longest sequence of \
words that can be displayed in the defined space and splits the text into lines to maximise \
the data that can be displayed.\n\nNewlines are also supported in the text widget using \
a single '\\n'";

/***			Internal Functions				***/



/***			External Functions				***/

ugui_window_t *text_window_create(uint32_t w, uint32_t h)
{
	text_window = ugui_window_create(w, h);

	text_widget = ugui_text_widget_create((ugui_rect_t) {.x = w / 8, .y = h / 8, .w = w / 8 * 6, .h = h / 8 * 6});

	ugui_text_widget_set_text(text_widget, &font_robotomono_regular_18, sample_one, 0);

	ugui_layer_t* base_layer = ugui_window_get_base_layer(text_window);

	ugui_layer_t* text_widget_layer = ugui_text_widget_get_layer(text_widget);

	ugui_layer_add_child(base_layer, text_widget_layer);

	return text_window;
}

void text_window_destroy()
{
	ugui_text_widget_destroy(text_widget);

	ugui_window_destroy(text_window);
}


