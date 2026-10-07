#include "settings_screen.h"

void draw_settings_screen(Canvas* canvas, AppContext* app) {
    canvas_clear(canvas);
    if(app->game_stats.sound_on) {
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound ON");
    } else {
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound OFF");
    }
    if(app->game_stats.vibration_on) {
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration ON");
    } else {
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration OFF");
    }
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, SETTINGS_RESET_Y, AlignLeft, AlignTop, "Reset");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, app->current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(app->current_y == SETTINGS_SOUND_Y)
        if(app->game_stats.sound_on) {
            elements_multiline_text_aligned(
                canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound ON");
        } else {
            elements_multiline_text_aligned(
                canvas, CHOICE_SCENE_X, SETTINGS_SOUND_Y, AlignLeft, AlignTop, "Sound OFF");
        }
    else if(app->current_y == SETTINGS_VIBRATION_Y)
        if(app->game_stats.vibration_on) {
            elements_multiline_text_aligned(
                canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration ON");
        } else {
            elements_multiline_text_aligned(
                canvas, CHOICE_SCENE_X, SETTINGS_VIBRATION_Y, AlignLeft, AlignTop, "Vibration OFF");
        }
    else if(app->current_y == SETTINGS_RESET_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, SETTINGS_RESET_Y, AlignLeft, AlignTop, "Reset");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, app->current_y, AlignRight, AlignTop, ">");
}
