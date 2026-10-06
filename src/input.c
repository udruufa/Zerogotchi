#include "init.h"
#include "input.h"
#include "stats.h"
#include "storage.h"
#include "mini_games/game_TicTacToe.h"
#include "mini_games/game_NoSignal.h"
#include "mini_games/game_Memory.h"

void input_callback(InputEvent* input_event, void* ctx) {
    furi_assert(ctx);
    AppContext* app = ctx;

    ZerogotchiEvent event = {.type = EventTypeInput, .input = *input_event};
    furi_message_queue_put(app->event_queue, &event, FuriWaitForever);
}

bool handle_input(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        if(app->action == waking_up) {
            app->action = sleeping;
        } else if(app->action == reset) {
            app->action = in_settings;
            app->current_y = SETTINGS_RESET_Y;
        } else if(app->animation.is_animating) {
            ;
        } else if(app->action != NONE) {
            app->action = NONE;
        } else {
            app->game_stats.last_save_time = furi_hal_rtc_get_timestamp();
            save_game(app);
            return true;
        }
    } else if(event->input.key == InputKeyUp) {
        if(app->action == eating) {
            if(app->current_y == FOOD_SARDINE_Y)
                app->current_y = FOOD_ICEFISH_Y;
            else if(app->current_y == FOOD_ICEFISH_Y)
                app->current_y -= 16;
            else
                app->current_y -= 12;
        } else if(app->action == playing) {
            if(app->current_y == GAMES_TICTACTOE_Y)
                app->current_y = GAMES_MEMORY_Y;
            else
                app->current_y -= 12;
        } else if(app->action == waking_up) {
            if(app->current_y == WAKE_UP_NO_Y) {
                app->current_y = WAKE_UP_YES_Y;
            }
        } else if(app->action == healing) {
            if(app->current_y == MEDICINES_VITAMINS_Y)
                app->current_y = MEDICINES_INJECTION_Y;
            else
                app->current_y -= 12;
        } else if(app->action == in_settings) {
            if(app->current_y == SETTINGS_SOUND_Y)
                app->current_y = SETTINGS_RESET_Y;
            else
                app->current_y -= 12;
        } else if(app->action == reset) {
            if(app->current_y == RESET_NO_Y) {
                app->current_y = RESET_YES_Y;
            }
        }
    } else if(event->input.key == InputKeyDown) {
        if(app->action == eating) {
            if(app->current_y == FOOD_ICEFISH_Y)
                app->current_y = FOOD_SARDINE_Y;
            else if(app->current_y == FOOD_MACKEREL_Y)
                app->current_y += 16;
            else
                app->current_y += 12;
        } else if(app->action == playing) {
            if(app->current_y == GAMES_MEMORY_Y)
                app->current_y = GAMES_TICTACTOE_Y;
            else
                app->current_y += 12;
        } else if(app->action == waking_up) {
            if(app->current_y == WAKE_UP_YES_Y) {
                app->current_y = WAKE_UP_NO_Y;
            }
        } else if(app->action == healing) {
            if(app->current_y == MEDICINES_INJECTION_Y)
                app->current_y = MEDICINES_VITAMINS_Y;
            else
                app->current_y += 12;
        } else if(app->action == in_settings) {
            if(app->current_y == SETTINGS_RESET_Y)
                app->current_y = SETTINGS_SOUND_Y;
            else
                app->current_y += 12;
        } else if(app->action == reset) {
            if(app->current_y == RESET_YES_Y) {
                app->current_y = RESET_NO_Y;
            }
        }
    } else if(event->input.key == InputKeyRight) {
        if(app->action == pet_selection) {
            app->game_stats.type = (app->game_stats.type + 1) % COUNT_TYPE;
        } else if(app->action == going_to_sleep) {
            if(app->current_x == GO_TO_SLEEP_YES_X) {
                app->current_x = GO_TO_SLEEP_NO_X;
            }
        } else if(!app->animation.is_animating && app->action == NONE)
            app->selectedAction = (app->selectedAction + 1) % COUNT_ACTION;
    } else if(event->input.key == InputKeyLeft) {
        if(app->action == pet_selection) {
            app->game_stats.type = (app->game_stats.type - 1 + COUNT_TYPE) % COUNT_TYPE;
        } else if(app->action == going_to_sleep) {
            if(app->current_x == GO_TO_SLEEP_NO_X) {
                app->current_x = GO_TO_SLEEP_YES_X;
            }
        } else if(!app->animation.is_animating && app->action == NONE)
            app->selectedAction = (app->selectedAction - 1 + COUNT_ACTION) % COUNT_ACTION;
    } else if(event->input.key == InputKeyOk) {
        if(!app->animation.is_animating) {
            if(app->action == NONE) {
                if(!app->game_stats.is_sleeping) {
                    switch(app->selectedAction) {
                    case eat:
                        if(app->game_stats.hunger < MAX_STAT) {
                            app->current_y = FOOD_SARDINE_Y;
                            app->action = eating;
                        } else {
                            app->animation.is_animating = true;
                            app->animation.frames = 8;
                            app->animation.animation_frame = 0;
                        }
                        break;
                    case pet:
                        add_exp(1, app);
                        increase_stat(&app->game_stats.happiness, 1); //happiness +1
                        app->animation.is_animating = true;
                        app->animation.frames = 8;
                        app->animation.animation_frame = 0;
                        break;
                    case play:
                        app->current_y = GAMES_TICTACTOE_Y;
                        app->action = playing;
                        break;
                    case sleep:
                        app->animation.is_animating = true;
                        app->animation.frames = 8;
                        app->animation.animation_frame = 0;
                        app->action = going_to_sleep;
                        app->current_x = GO_TO_SLEEP_YES_X;
                        break;
                    case heal:
                        if(app->game_stats.health < MAX_STAT) {
                            app->current_y = MEDICINES_VITAMINS_Y;
                            app->action = healing;
                        } else {
                            app->animation.is_animating = true;
                            app->animation.frames = 8;
                            app->animation.animation_frame = 0;
                        }
                        break;
                    case info:
                        app->action = informing;
                        break;
                    case settings:
                        app->current_y = SETTINGS_SOUND_Y;
                        app->action = in_settings;
                        break;
                    default:
                        break;
                    }
                } else {
                    switch(app->selectedAction) {
                    case info:
                        app->action = informing;
                        break;
                    default:
                        app->action = sleeping;
                        break;
                    }
                }
            } else {
                switch(app->action) {
                case eating:
                    add_exp(2, app);
                    if(app->current_y == FOOD_SARDINE_Y) {
                        increase_stat(&app->game_stats.happiness, 1); //happiness +1
                        increase_stat(&app->game_stats.hunger, 2); //hunger +2
                    } else if(app->current_y == FOOD_SQUID_Y) {
                        increase_stat(&app->game_stats.hunger, 3); //hunger +3
                    } else if(app->current_y == FOOD_MACKEREL_Y) {
                        increase_stat(&app->game_stats.happiness, 2); //happiness +2
                        increase_stat(&app->game_stats.hunger, 1); //hunger +1
                    } else if(app->current_y == FOOD_ICEFISH_Y) {
                        decrease_stat(&app->game_stats.health, 2); //health -2
                        increase_stat(&app->game_stats.happiness, 2); //happiness +2
                        increase_stat(&app->game_stats.hunger, 4); //hunger +4
                    }
                    app->action = NONE;
                    break;
                case playing:
                    if(app->current_y == GAMES_TICTACTOE_Y) {
                        app->action = game_TicTacToe;
                        init_new_game_TicTacToe();
                    } else if(app->current_y == GAMES_NOSIGNAL_Y) {
                        app->action = game_NoSignal;
                        app->animation.is_animating = true;
                        app->animation.frames = 2;
                        app->animation.animation_frame = 0;
                        init_new_game_NoSignal();
                    } else if(app->current_y == GAMES_MEMORY_Y) {
                        app->action = game_Memory;
                        init_new_game_Memory();
                    }
                    break;
                case going_to_sleep:
                    if(app->current_x == GO_TO_SLEEP_YES_X) {
                        app->action = sleeping;
                        app->game_stats.sleep_time = 28800;
                        app->game_stats.is_sleeping = true;
                    } else if(app->current_x == GO_TO_SLEEP_NO_X) {
                        app->action = NONE;
                    }
                    break;
                case sleeping:
                    app->current_y = WAKE_UP_YES_Y;
                    app->action = waking_up;
                    break;
                case waking_up:
                    if(app->current_y == WAKE_UP_YES_Y) {
                        if(app->game_stats.sleep_time == 0) {
                            add_exp(10, app);
                        }
                        decrease_stat(&app->game_stats.health, 5); //health -5
                        decrease_stat(&app->game_stats.happiness, 12); //happiness -12
                        app->animation.is_animating = false;
                        app->game_stats.is_sleeping = false;
                    }
                    app->action = NONE;
                    break;
                case healing:
                    add_exp(1, app);
                    if(app->current_y == MEDICINES_VITAMINS_Y) {
                        increase_stat(&app->game_stats.health, 2); //health +2
                        decrease_stat(&app->game_stats.happiness, 1); //happiness -1
                    } else if(app->current_y == MEDICINES_PILLS_Y) {
                        increase_stat(&app->game_stats.health, 4); //health +4
                        decrease_stat(&app->game_stats.happiness, 2); //happiness -2
                    } else if(app->current_y == MEDICINES_INJECTION_Y) {
                        increase_stat(&app->game_stats.health, 5); //health +5
                        decrease_stat(&app->game_stats.happiness, 4); //happiness -4
                    }
                    app->action = NONE;
                    break;
                case informing:
                    app->action = NONE;
                    break;
                case in_settings:
                    if(app->current_y == SETTINGS_SOUND_Y) {
                        app->game_stats.sound_on = true;
                    } else if(app->current_y == SETTINGS_VIBRATION_Y) {
                        app->game_stats.vibration_on = true;
                    } else if(app->current_y == SETTINGS_RESET_Y) {
                        app->action = reset;
                        app->current_y = RESET_YES_Y;
                    }
                    break;
                case reset:
                    if(app->current_y == RESET_YES_Y) {
                        app->action = pet_selection;
                    } else if(app->current_y == RESET_NO_Y) {
                        app->action = in_settings;
                        app->current_y = SETTINGS_RESET_Y;
                    }
                    break;
                case pet_selection:
                    init_new_game(app);
                    app->action = NONE;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return false;
}
