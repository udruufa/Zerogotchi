#include "game_TicTacToe.h"

static int32_t square_x;
static int32_t square_y;

static int32_t opponent_square;

static uint32_t squares_count;

static int32_t initial_check[3][3][3] = {
    {{0, X1, Y1}, {0, X2, Y1}, {0, X3, Y1}},
    {{0, X1, Y2}, {0, X2, Y2}, {0, X3, Y2}},
    {{0, X1, Y3}, {0, X2, Y3}, {0, X3, Y3}},
};

static int32_t check[3][3][3];
static bool is_win;
static bool is_lose;

void init_new_game_TicTacToe() {
    square_x = X1;
    square_y = Y1;
    squares_count = 9;

    memcpy(check, initial_check, sizeof(check));

    is_win = false;
    is_lose = false;
}

void handle_input_game_TicTacToe(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        if(is_win)
            add_exp(8, app);
        else if(is_lose)
            add_exp(2, app);
        else if(!squares_count)
            add_exp(3, app);
        increase_stat(&app->game_stats.happiness, 5); //happiness +5
        decrease_stat(&app->game_stats.hunger, 3); //hunger -3
        app->action = playing;
    } else if(event->input.key == InputKeyUp) {
        if(square_y == Y1)
            square_y = Y3;
        else
            square_y -= MOVEMENT;
    } else if(event->input.key == InputKeyDown) {
        if(square_y == Y3)
            square_y = Y1;
        else
            square_y += MOVEMENT;
    } else if(event->input.key == InputKeyRight) {
        if(square_x == X3)
            square_x = X1;
        else
            square_x += MOVEMENT;
    } else if(event->input.key == InputKeyLeft) {
        if(square_x == X1)
            square_x = X3;
        else
            square_x -= MOVEMENT;
    } else if(event->input.key == InputKeyOk) {
        if(squares_count && !is_win && !is_lose) {
            for(int32_t i = 0; i < 3; i++) {
                for(int32_t j = 0; j < 3; j++) {
                    if(square_x == check[i][j][1] && square_y == check[i][j][2] &&
                       check[i][j][0] == 0) {
                        check[i][j][0] = 1;
                        squares_count--;

                        if((check[i][0][0] == 1 && check[i][1][0] == 1 && check[i][2][0] == 1) ||
                           (check[0][j][0] == 1 && check[1][j][0] == 1 && check[2][j][0] == 1) ||
                           (check[0][0][0] == 1 && check[1][1][0] == 1 && check[2][2][0] == 1) ||
                           (check[0][2][0] == 1 && check[1][1][0] == 1 && check[2][0][0] == 1)) {
                            is_win = true;
                        }

                        while(squares_count) {
                            opponent_square = rand() % 9;
                            if(check[opponent_square / 3][opponent_square % 3][0] == 0) {
                                check[opponent_square / 3][opponent_square % 3][0] = -1;
                                squares_count--;

                                if((check[opponent_square / 3][0][0] == -1 &&
                                    check[opponent_square / 3][1][0] == -1 &&
                                    check[opponent_square / 3][2][0] == -1) ||
                                   (check[0][opponent_square % 3][0] == -1 &&
                                    check[1][opponent_square % 3][0] == -1 &&
                                    check[2][opponent_square % 3][0] == -1) ||
                                   (check[0][0][0] == -1 && check[1][1][0] == -1 &&
                                    check[2][2][0] == -1) ||
                                   (check[0][2][0] == -1 && check[1][1][0] == -1 &&
                                    check[2][0][0] == -1))
                                    is_lose = true;

                                break;
                            }
                        }
                        break;
                    }
                }
            }
        } else {
            if(is_win)
                add_exp(8, app);
            else if(is_lose)
                add_exp(2, app);
            else if(!squares_count)
                add_exp(3, app);
            increase_stat(&app->game_stats.happiness, 5); //happiness +5
            decrease_stat(&app->game_stats.hunger, 3); //hunger -3
            init_new_game_TicTacToe();
        }
    }
}

void draw_game_TicTacToe(Canvas* canvas) {
    canvas_clear(canvas);

    canvas_draw_icon(canvas, 0, 37, &I_hands);
    canvas_draw_icon(canvas, 0, 0, &I_dolphins_hands);

    canvas_draw_icon(canvas, 39, 7, &I_board);

    canvas_draw_icon(canvas, square_x, square_y, &I_square);

    for(uint32_t i = 0; i < 3; i++) {
        for(uint32_t j = 0; j < 3; j++) {
            if(check[i][j][0] == 1) {
                canvas_draw_icon(canvas, check[i][j][1], check[i][j][2], &I_x);
                if(square_x == check[i][j][1] && square_y == check[i][j][2])
                    canvas_draw_icon(canvas, check[i][j][1], check[i][j][2], &I_x_hover);
            } else if(check[i][j][0] == -1) {
                canvas_draw_icon(canvas, check[i][j][1], check[i][j][2], &I_o);
                if(square_x == check[i][j][1] && square_y == check[i][j][2])
                    canvas_draw_icon(canvas, check[i][j][1], check[i][j][2], &I_o_hover);
            }
        }
    }

    if(is_win) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "YOU WIN!");
    } else if(is_lose) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "YOU LOSE:(");
    } else if(!squares_count) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "THE DRAW.");
    }
}
