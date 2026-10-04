#include "settings_screen.h"

void draw_settings_screen(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, SETTINGS_RESET_Y, AlignLeft, AlignTop, "Reset");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == SETTINGS_SOUND_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound");
    else if(current_y == SETTINGS_VIBRATION_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration");
    else if(current_y == SETTINGS_RESET_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_RESET_Y, AlignLeft, AlignTop, "Reset");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
