#include "heal_scene.h"

void draw_heal_scene(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, MEDICINES_VITAMINS_Y, AlignLeft, AlignTop, "Vitamins");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, MEDICINES_PILLS_Y, AlignLeft, AlignTop, "Pills");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, MEDICINES_INJECTION_Y, AlignLeft, AlignTop, "Injection");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == MEDICINES_VITAMINS_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, MEDICINES_VITAMINS_Y, AlignLeft, AlignTop, "Vitamins");
    else if(current_y == MEDICINES_PILLS_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, MEDICINES_PILLS_Y, AlignLeft, AlignTop, "Pills");
    else if(current_y == MEDICINES_INJECTION_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, MEDICINES_INJECTION_Y, AlignLeft, AlignTop, "Injection");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
