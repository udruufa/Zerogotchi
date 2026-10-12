#include "game_Memory.h"
#include "../feedback.h"

static uint32_t count;

uint32_t* order = NULL;

static bool is_showing;
static bool is_playing;
static bool show_pause;

static uint8_t arrow;
static uint8_t show_index;
static uint8_t input_index;

static bool is_win;
static bool is_lose;

void init_new_game_Memory() {
    count = 2;

    free(order);
    order = malloc(count * sizeof(uint32_t));

    show_pause = false;

    arrow = 0;
    show_index = 0;
    input_index = 0;

    is_showing = true;
    is_playing = false;

    is_win = false;
    is_lose = false;
}

void handle_input_game_Memory(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        app->action = playing;
    } else if(is_lose && event->input.key == InputKeyOk) {
        add_exp(3, app);
        increase_stat(&app->game_stats.happiness, 3); //happiness +3
        decrease_stat(&app->game_stats.hunger, 2); //hunger -2
        init_new_game_Memory();
        app->feedbacked = false;
    }
    if(!is_showing) {
        if(event->input.key == InputKeyUp) {
            arrow = 1;
            is_playing = true;
        } else if(event->input.key == InputKeyDown) {
            arrow = 2;
            is_playing = true;
        } else if(event->input.key == InputKeyRight) {
            arrow = 3;
            is_playing = true;
        } else if(event->input.key == InputKeyLeft) {
            arrow = 4;
            is_playing = true;
        }
    }
}

void draw_game_Memory(Canvas* canvas, AppContext* app) {
    canvas_clear(canvas);

    if(is_win) {
        is_win = false;
        show_index = 0;
        input_index = 0;
        is_showing = true;
        is_playing = false;
        count += 1;
        order = malloc(count * sizeof(uint32_t));
        if(app->game_stats.sound_on && !app->feedbacked) {
            app->sound = WIN;
            feedback_sound(app);
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
    } else {
        if(is_showing) {
            if(show_index < count) {
                if(show_pause) {
                    furi_delay_tick(500);
                    show_index++;
                    show_pause = false;
                } else {
                    uint8_t show_arrow = 1 + rand() % 4;

                    switch(show_arrow) {
                    case 1:
                        canvas_draw_icon(canvas, 57, 25, &I_arrow_up);
                        break;
                    case 2:
                        canvas_draw_icon(canvas, 57, 25, &I_arrow_down);
                        break;
                    case 3:
                        canvas_draw_icon(canvas, 57, 25, &I_arrow_right);
                        break;
                    case 4:
                        canvas_draw_icon(canvas, 57, 25, &I_arrow_left);
                        break;
                    default:
                        break;
                    }

                    furi_delay_tick(200);
                    show_pause = true;

                    order[show_index] = show_arrow;
                }
            } else {
                is_showing = false;
            }
        } else if(is_playing) {
            if(input_index < count) {
                switch(arrow) {
                case 1:
                    canvas_draw_icon(canvas, 57, 25, &I_arrow_up);
                    if(arrow != order[input_index]) {
                        is_lose = true;
                    }
                    input_index++;
                    arrow = 0;
                    break;
                case 2:
                    canvas_draw_icon(canvas, 57, 25, &I_arrow_down);
                    if(arrow != order[input_index]) {
                        is_lose = true;
                    }
                    input_index++;
                    arrow = 0;
                    break;
                case 3:
                    canvas_draw_icon(canvas, 57, 25, &I_arrow_right);
                    if(arrow != order[input_index]) {
                        is_lose = true;
                    }
                    input_index++;
                    arrow = 0;
                    break;
                case 4:
                    canvas_draw_icon(canvas, 57, 25, &I_arrow_left);
                    if(arrow != order[input_index]) {
                        is_lose = true;
                    }
                    input_index++;
                    arrow = 0;
                    break;
                default:
                    furi_delay_tick(250);
                    break;
                }
            } else {
                is_win = true;
            }
        }
    }
}
