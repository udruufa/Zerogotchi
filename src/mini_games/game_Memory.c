#include "game_Memory.h"

static uint32_t count;

uint32_t* arr = NULL;

static bool is_playing;

static bool up;
static bool right;
static bool down;
static bool left;

void init_new_game_Memory() {
    count = 4;

    free(arr);
    arr = NULL;

    is_playing = false;
}

void handle_input_game_Memory(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        app->action = playing;
    } else if(event->input.key == InputKeyUp) {
        up = true;
    } else if(event->input.key == InputKeyDown) {
        down = true;
    } else if(event->input.key == InputKeyRight) {
        right = true;
    } else if(event->input.key == InputKeyLeft) {
        left = true;
    } else if(event->input.key == InputKeyOk) {
        add_exp(3, app);
        increase_stat(&app->game_stats.happiness, 3); //happiness +3
        decrease_stat(&app->game_stats.hunger, 2); //hunger -2
        init_new_game_Memory();
    }
}

void draw_game_Memory(Canvas* canvas) {
    canvas_clear(canvas);

    if(!is_playing) {
        uint32_t i = 0;
        if(count) {
            arr = (uint32_t*)malloc(count * sizeof(uint32_t));

            uint32_t arrow = rand() % 4;

            // switch(arrow) {
            // case 0:
            //     canvas_draw_icon(canvas, 57, 25, &I_arrow_up);
            //     break;
            // case 1:
            //     canvas_draw_icon(canvas, 57, 25, &I_arrow_right);
            //     break;
            // case 2:
            //     canvas_draw_icon(canvas, 57, 25, &I_arrow_down);
            //     break;
            // case 3:
            //     canvas_draw_icon(canvas, 57, 25, &I_arrow_left);
            //     break;
            // default:
            //     break;
            // }

            furi_delay_tick(500);

            arr[i] = arrow;

            i++;
            count--;
        } else {
            is_playing = true;
        }
    } else {
        // if(up) {
        //     canvas_draw_icon(canvas, 57, 25, &I_arrow_up);
        //     up = false;
        // } else if(right) {
        //     canvas_draw_icon(canvas, 57, 25, &I_arrow_right);
        //     right = false;
        // } else if(down) {
        //     canvas_draw_icon(canvas, 57, 25, &I_arrow_down);
        //     down = false;
        // } else if(left) {
        //     canvas_draw_icon(canvas, 57, 25, &I_arrow_left);
        //     left = false;
        // }
    }
}
