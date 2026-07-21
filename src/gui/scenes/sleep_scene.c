#include "sleep_scene.h"

void draw_going_to_sleep_scene(Canvas* canvas, uint32_t current_x) {
    canvas_clear(canvas);

    canvas_draw_icon(canvas, 0, 0, &I_go_to_sleep_scene);

    canvas_draw_icon(canvas, 10, 50, &I_sleep_btn);
    canvas_draw_icon(canvas, 68, 50, &I_sleep_btn);

    elements_multiline_text_aligned(
        canvas, GO_TO_SLEEP_YES_X, 56, AlignCenter, AlignCenter, "Go to sleep");
    elements_multiline_text_aligned(
        canvas, GO_TO_SLEEP_NO_X, 56, AlignCenter, AlignCenter, "Not now");

    // canvas_invert_color(canvas);

    if(current_x == GO_TO_SLEEP_YES_X) {
        canvas_draw_icon(canvas, 10, 50, &I_sleep_btn_hover);
        canvas_invert_color(canvas);
        elements_multiline_text_aligned(
            canvas, GO_TO_SLEEP_YES_X, 56, AlignCenter, AlignCenter, "Go to sleep");
        canvas_invert_color(canvas);
    } else if(current_x == GO_TO_SLEEP_NO_X) {
        canvas_draw_icon(canvas, 68, 50, &I_sleep_btn_hover);
        canvas_invert_color(canvas);
        elements_multiline_text_aligned(
            canvas, GO_TO_SLEEP_NO_X, 56, AlignCenter, AlignCenter, "Not now");
        canvas_invert_color(canvas);
    }
}

void draw_sleep_scene(Canvas* canvas, AppContext* app) {
    char time[32];

    uint32_t hours = app->game_stats.sleep_time / 3600;
    uint32_t minutes = (app->game_stats.sleep_time % 3600) / 60;
    uint32_t seconds = app->game_stats.sleep_time % 60;

    canvas_clear(canvas);

    canvas_draw_icon(canvas, 0, 0, &I_sleep_scene);

    canvas_set_font(canvas, FontSecondary);

    snprintf(time, sizeof(time), "%02lu:%02lu:%02lu", hours, minutes, seconds);
    elements_multiline_text_aligned(canvas, 98, 15, AlignCenter, AlignCenter, time);
    canvas_invert_color(canvas);
    elements_multiline_text_aligned(canvas, 98, 27, AlignCenter, AlignCenter, "WAKE UP");
}

void draw_wake_up_scene(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    canvas_set_font(canvas, FontPrimary);

    elements_multiline_text_aligned(
        canvas, 64, WAKE_UP_SURE_Y, AlignCenter, AlignTop, "Are you sure?");

    canvas_set_font(canvas, FontSecondary);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, WAKE_UP_YES_Y, AlignLeft, AlignTop, "Yes");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, WAKE_UP_NO_Y, AlignLeft, AlignTop, "No");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == WAKE_UP_YES_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, WAKE_UP_YES_Y, AlignLeft, AlignTop, "Yes");
    else if(current_y == WAKE_UP_NO_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, WAKE_UP_NO_Y, AlignLeft, AlignTop, "No");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
