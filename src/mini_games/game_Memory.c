#include "game_Memory.h"

void init_new_game_Memory() {
}

void handle_input_game_Memory(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        app->action = playing;
    } else if(event->input.key == InputKeyUp) {
    } else if(event->input.key == InputKeyDown) {
    } else if(event->input.key == InputKeyRight) {
    } else if(event->input.key == InputKeyLeft) {
    } else if(event->input.key == InputKeyOk) {
        add_exp(3, app);
        increase_stat(&app->game_stats.happiness, 3); //happiness +3
        decrease_stat(&app->game_stats.hunger, 2); //hunger -2
        init_new_game_Memory();
    }
}

void draw_game_Memory(Canvas* canvas) {
    canvas_clear(canvas);
}
