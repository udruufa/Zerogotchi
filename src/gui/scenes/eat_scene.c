#include "eat_scene.h"

void draw_eat_scene(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_SARDINE_Y, AlignLeft, AlignTop, "Sardine");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_SQUID_Y, AlignLeft, AlignTop, "Squid");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_MACKEREL_Y, AlignLeft, AlignTop, "Mackerel");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_ICEFISH_Y, AlignLeft, AlignTop, "Icefish");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == FOOD_SARDINE_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_SARDINE_Y, AlignLeft, AlignTop, "Sardine");
    else if(current_y == FOOD_SQUID_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_SQUID_Y, AlignLeft, AlignTop, "Squid");
    else if(current_y == FOOD_MACKEREL_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_MACKEREL_Y, AlignLeft, AlignTop, "Mackerel");
    else if(current_y == FOOD_ICEFISH_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_ICEFISH_Y, AlignLeft, AlignTop, "Icefish");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
