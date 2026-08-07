#include "menu_view.h"

void draw_menu_view(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    canvas_draw_icon(canvas, 0, 1, &I_menu_title);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, MENU_QUIT_Y, AlignLeft, AlignTop, "QUIT");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, MENU_SETTINGS_Y, AlignLeft, AlignTop, "SETTINGS");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 3, 128, 13);

    canvas_invert_color(canvas);

    if(current_y == MENU_QUIT_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, MENU_QUIT_Y, AlignLeft, AlignTop, "QUIT");
    else if(current_y == MENU_SETTINGS_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, MENU_SETTINGS_Y, AlignLeft, AlignTop, "SETTINGS");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
