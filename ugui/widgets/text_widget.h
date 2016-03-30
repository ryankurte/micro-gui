
#ifndef TEXT_WIDGET_H
#define TEXT_WIDGET_H

#include <stdint.h>

#include "ugui/ugui.h"

#ifdef __cplusplus
extern "C" {
#endif

enum ugui_text_alignment_e {
	UGUI_TEXT_ALIGN_LEFT,
	UGUI_TEXT_ALIGN_CENTER,
	UGUI_TEXT_ALIGN_RIGHT
};

typedef struct ugui_text_widget_s ugui_text_widget_t;

ugui_text_widget_t *ugui_text_widget_create(ugui_rect_t frame);

void ugui_text_widget_set_text(ugui_text_widget_t* text_widget, font_style_t *font, char* text, uint8_t alignment);

ugui_layer_t* ugui_text_widget_get_layer(ugui_text_widget_t* text_widget);

void ugui_text_widget_destroy(ugui_text_widget_t* text_widget);

#ifdef __cplusplus
}
#endif

#endif
