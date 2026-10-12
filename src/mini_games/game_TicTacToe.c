#include "game_TicTacToe.h"
#include "../feedback.h"

static int32_t square_x;
static int32_t square_y;

static uint32_t squares_count;

static int32_t initial_check[3][3][3] = {
    {{0, X1, Y1}, {0, X2, Y1}, {0, X3, Y1}},
    {{0, X1, Y2}, {0, X2, Y2}, {0, X3, Y2}},
    {{0, X1, Y3}, {0, X2, Y3}, {0, X3, Y3}},
};

static int32_t check[3][3][3];
static bool is_win;
static bool is_lose;

static bool computer_checked;

void init_new_game_TicTacToe() {
    square_x = X1;
    square_y = Y1;
    squares_count = 9;

    memcpy(check, initial_check, sizeof(check));

    is_win = false;
    is_lose = false;

    computer_checked = false;
}

void compiter_input(uint32_t row, uint32_t column) {
    check[row][column][0] = -1;

    if((check[row][0][0] == -1 && check[row][1][0] == -1 && check[row][2][0] == -1) ||
       (check[0][column][0] == -1 && check[1][column][0] == -1 && check[2][column][0] == -1) ||
       (check[0][0][0] == -1 && check[1][1][0] == -1 && check[2][2][0] == -1) ||
       (check[0][2][0] == -1 && check[1][1][0] == -1 && check[2][0][0] == -1))
        is_lose = true;

    squares_count--;
    computer_checked = true;
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

                        while(!computer_checked) {
                            for(uint8_t i = 0; i < 3; i++) {
                                if((check[i][0][0] + check[i][1][0] + check[i][2][0]) == -2) {
                                    for(uint8_t j = 0; j < 3; j++) {
                                        if(check[i][j][0] == 0) {
                                            compiter_input(i, j);
                                            break;
                                        }
                                    }
                                } else if((check[0][i][0] + check[1][i][0] + check[2][i][0]) == -2) {
                                    for(uint8_t j = 0; j < 3; j++) {
                                        if(check[j][i][0] == 0) {
                                            compiter_input(j, i);
                                            break;
                                        }
                                    }
                                } else if((check[0][0][0] + check[1][1][0] + check[2][2][0]) == -2) {
                                    for(uint8_t k = 0; k < 3; k++) {
                                        if(check[k][k][0] == 0) {
                                            compiter_input(k, k);
                                            break;
                                        }
                                    }
                                } else if((check[0][2][0] + check[1][1][0] + check[2][0][0]) == -2) {
                                    uint8_t l = 2;
                                    for(uint8_t k = 0; k < 3; k++) {
                                        if(check[k][l][0] == 0) {
                                            compiter_input(k, l);
                                            break;
                                        }
                                        l--;
                                    }
                                }
                                if(computer_checked) break;
                            }
                            for(uint8_t i = 0; i < 3; i++) {
                                if((check[i][0][0] + check[i][1][0] + check[i][2][0]) == 2) {
                                    for(uint8_t j = 0; j < 3; j++) {
                                        if(check[i][j][0] == 0) {
                                            compiter_input(i, j);
                                            break;
                                        }
                                    }
                                } else if((check[0][i][0] + check[1][i][0] + check[2][i][0]) == 2) {
                                    for(uint8_t j = 0; j < 3; j++) {
                                        if(check[j][i][0] == 0) {
                                            compiter_input(j, i);
                                            break;
                                        }
                                    }
                                } else if((check[0][0][0] + check[1][1][0] + check[2][2][0]) == 2) {
                                    for(uint8_t k = 0; k < 3; k++) {
                                        if(check[k][k][0] == 0) {
                                            compiter_input(k, k);
                                            break;
                                        }
                                    }
                                } else if((check[0][2][0] + check[1][1][0] + check[2][0][0]) == 2) {
                                    uint8_t l = 2;
                                    for(uint8_t k = 0; k < 3; k++) {
                                        if(check[k][l][0] == 0) {
                                            compiter_input(k, l);
                                            break;
                                        }
                                        l--;
                                    }
                                }
                                if(computer_checked) break;
                            }
                            if(!computer_checked) {
                                if(check[1][1][0] == 0) {
                                    compiter_input(1, 1);
                                } else {
                                    while(squares_count) {
                                        int32_t opponent_square = rand() % 9;
                                        if(check[opponent_square / 3][opponent_square % 3][0] ==
                                           0) {
                                            compiter_input(
                                                opponent_square / 3, opponent_square % 3);
                                            break;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                        break;
                    }
                }
            }
            computer_checked = false;
        } else {
            if(is_win)
                add_exp(8, app);
            else if(is_lose)
                add_exp(2, app);
            else if(!squares_count)
                add_exp(3, app);
            increase_stat(&app->game_stats.happiness, 5); //happiness +5
            decrease_stat(&app->game_stats.hunger, 3); //hunger -3
            app->feedbacked = false;
            init_new_game_TicTacToe();
        }
    }
}

void draw_game_TicTacToe(Canvas* canvas, AppContext* app) {
    canvas_clear(canvas);

    canvas_draw_icon(canvas, 0, 37, &I_hands);
    switch(app->game_stats.type) {
    case(DOLPHIN):
        canvas_draw_icon(canvas, 0, 0, &I_dolphin_hands);
        break;
    case(DRAGON):
        canvas_draw_icon(canvas, 0, 0, &I_dragon_hands);
        break;
    case(RABBIT):
        canvas_draw_icon(canvas, 0, 0, &I_rabbit_hands);
        break;
    case(TURTLE):
        canvas_draw_icon(canvas, 0, 0, &I_turtle_hands);
        break;
    default:
        break;
    }

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
        if(app->game_stats.sound_on && !app->feedbacked) {
            app->sound = WIN;
            feedback_sound(app);
            app->feedbacked = true;
        }
    } else if(is_lose) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "YOU LOSE:(");
        if(app->game_stats.sound_on && !app->feedbacked) {
            app->sound = LOSS;
            feedback_sound(app);
            app->feedbacked = true;
        }
    } else if(!squares_count) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "THE DRAW.");
        if(app->game_stats.sound_on && !app->feedbacked) {
            app->sound = END;
            feedback_sound(app);
            app->feedbacked = true;
        }
    }
}
