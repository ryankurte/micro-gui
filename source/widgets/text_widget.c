
#include "ugui/widgets/text_widget.h"
#include "ugui/font.h"

#include <stdlib.h>
#include <assert.h>


struct ugui_text_widget_s {
    ugui_layer_t* widget_layer;

    font_style_t *font;
    uint8_t alignment;
    char* text;
};

char* fake_text = "text widget default text";

// TODO: this whole module is awful
// this method in particular needs refactoring
// Also, do we really need everything to derive from a layer? Seems wasteful when only some
// objects can actually contain children, and as such this would be more sensible as a
// "text area" or something.
// TODO: support text justification
static void text_widget_layer_update(ugui_layer_t* layer, void* graphics_ctx, void* layer_ctx)
{
    ugui_text_widget_t* text_widget = (ugui_text_widget_t*) layer_ctx;
    ugui_rect_t* bounds = ugui_layer_get_bounds(layer);

    uint8_t line_buff[64];

    ugui_size_t text_size;
    // TODO: dirty hack will only support monospace fonts
    ugui_font_get_text_size(text_widget->font,
                            "A",
                            &text_size);

    uint16_t max_text_width = bounds->w / text_size.w;
    uint16_t max_text_lines = bounds->h / text_size.h;

    uint16_t len = strlen(text_widget->text);

    uint16_t line_index = 0;
    uint16_t line_count = 0;
    uint16_t offset = 0;
    uint16_t alignment_offset = 0;

    while ((offset < len) && (line_index < max_text_lines)) {

        // Determine line length
        for (int i = 0; i < max_text_width; i++) {
            // Handle end of text
            if ((offset + i) >= len) {
                line_count = i;
                break;
            }

            // Handle newlines
            if (text_widget->text[offset + i] == '\n') {
                line_count = i;
                break;
            }

            // Insert linebreaks up to spaces.
            if (text_widget->text[offset + i] == ' ') {
                line_count = i;
            }
        }

        // Copy line into line buffer for rendering
        strncpy(line_buff, text_widget->text + offset, line_count);
        line_buff[line_count] = '\0';

        // Calculate offset for alignment modes
        switch (text_widget->alignment) {
        case UGUI_TEXT_ALIGN_LEFT:
            alignment_offset = 0;
            break;
        case UGUI_TEXT_ALIGN_CENTER:
            alignment_offset = (max_text_width - line_count) / 2;
            break;
        case UGUI_TEXT_ALIGN_RIGHT:
            alignment_offset = (max_text_width - line_count);
            break;
        }

        ugui_graphics_draw_text(graphics_ctx,
                                line_buff,
                                text_widget->font,
        (ugui_point_t) {
            .x = alignment_offset * text_size.w, .y = line_index * text_size.h
        });

        offset += line_count + 1;
        line_index += 1;
    }
}

ugui_text_widget_t *ugui_text_widget_create(ugui_rect_t bounds)
{
    ugui_text_widget_t* text_widget = (ugui_text_widget_t*)malloc(sizeof(ugui_text_widget_t));

    text_widget->widget_layer = ugui_layer_create(bounds);

    // Set defaults
    text_widget->text = fake_text;
    text_widget->font = FONT_DEFAULT;

    // Bind update method
    ugui_layer_set_update(text_widget->widget_layer, text_widget_layer_update);
    // Bind text_widget instance to layer context for use in update and other calls
    ugui_layer_set_ctx(text_widget->widget_layer, (void*) text_widget);

    return text_widget;
}

void ugui_text_widget_set_text(ugui_text_widget_t* text_widget, font_style_t* font, char* text, uint8_t alignment)
{
    text_widget->text = text;
    text_widget->font = font;
    text_widget->alignment = alignment;
}

void ugui_text_widget_destroy(ugui_text_widget_t* text_widget)
{
    ugui_layer_destroy(text_widget->widget_layer);

    free(text_widget);
}

ugui_layer_t* ugui_text_widget_get_layer(ugui_text_widget_t* text_widget)
{
    return text_widget->widget_layer;
}
