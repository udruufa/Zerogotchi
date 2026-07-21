#include "play_scene.h"

void draw_play_scene(Canvas* canvas, uint32_t current_y) {
    canvas_clear(canvas);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, GAMES_TICTACTOE_Y, AlignLeft, AlignTop, "Tic Tac Toe");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, GAMES_NOSIGNAL_Y, AlignLeft, AlignTop, "No Signal");
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, GAMES_MEMORY_Y, AlignLeft, AlignTop, "Memory");

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == GAMES_TICTACTOE_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, GAMES_TICTACTOE_Y, AlignLeft, AlignTop, "Tic Tac Toe");
    else if(current_y == GAMES_NOSIGNAL_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, GAMES_NOSIGNAL_Y, AlignLeft, AlignTop, "No Signal");
    else if(current_y == GAMES_MEMORY_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, GAMES_MEMORY_Y, AlignLeft, AlignTop, "Memory");

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
