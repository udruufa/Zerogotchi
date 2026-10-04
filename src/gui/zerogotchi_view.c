#include "zerogotchi_view.h"
#include "settings_screen.h"
#include "reset_screen.h"
#include "scenes/eat_scene.h"
#include "scenes/play_scene.h"
#include "scenes/heal_scene.h"
#include "scenes/info_scene.h"
#include "scenes/sleep_scene.h"
#include "../mini_games/game_TicTacToe.h"
#include "../mini_games/game_NoSignal.h"
#include "../mini_games/game_Memory.h"

// DOLPHIN

static const Icon* dolphin_baby_frames[] = {
    &I_dolphin_baby_0,
    &I_dolphin_baby_1,
    &I_dolphin_baby_2,
    &I_dolphin_baby_3,
};
static const Icon* dolphin_baby_sleeping_frames[] = {
    &I_dolphin_baby_sleeping_0,
    &I_dolphin_baby_sleeping_1,
    &I_dolphin_baby_sleeping_2,
    &I_dolphin_baby_sleeping_3,
};

static const Icon* dolphin_teen_frames[] = {
    &I_dolphin_teen_0,
    &I_dolphin_teen_1,
    &I_dolphin_teen_2,
    &I_dolphin_teen_3,
};
static const Icon* dolphin_teen_sleeping_frames[] = {
    &I_dolphin_teen_sleeping_0,
    &I_dolphin_teen_sleeping_1,
    &I_dolphin_teen_sleeping_2,
    &I_dolphin_teen_sleeping_3,
};

static const Icon* dolphin_adult_frames[] = {
    &I_dolphin_adult_0,
    &I_dolphin_adult_1,
    &I_dolphin_adult_2,
    &I_dolphin_adult_3,
};
static const Icon* dolphin_adult_sleeping_frames[] = {
    &I_dolphin_adult_sleeping_0,
    &I_dolphin_adult_sleeping_1,
    &I_dolphin_adult_sleeping_2,
    &I_dolphin_adult_sleeping_3,
};

static const Icon* dolphin_pet_frames[] = {
    &I_dolphin_pet_animation_0,
    &I_dolphin_pet_animation_1,
    &I_dolphin_pet_animation_2,
    &I_dolphin_pet_animation_3,
    &I_dolphin_pet_animation_4,
    &I_dolphin_pet_animation_5,
    &I_dolphin_pet_animation_6,
    &I_dolphin_pet_animation_7,
};

// DRAGON

static const Icon* dragon_baby_frames[] = {
    &I_dragon_baby_0,
    &I_dragon_baby_1,
    &I_dragon_baby_2,
    &I_dragon_baby_3,
};
static const Icon* dragon_baby_sleeping_frames[] = {
    &I_dragon_baby_sleeping_0,
    &I_dragon_baby_sleeping_1,
    &I_dragon_baby_sleeping_2,
    &I_dragon_baby_sleeping_3,
};

static const Icon* dragon_teen_frames[] = {
    &I_dragon_teen_0,
    &I_dragon_teen_1,
    &I_dragon_teen_2,
    &I_dragon_teen_3,
};
static const Icon* dragon_teen_sleeping_frames[] = {
    &I_dragon_teen_sleeping_0,
    &I_dragon_teen_sleeping_1,
    &I_dragon_teen_sleeping_2,
    &I_dragon_teen_sleeping_3,
};

static const Icon* dragon_adult_frames[] = {
    &I_dragon_adult_0,
    &I_dragon_adult_1,
    &I_dragon_adult_2,
    &I_dragon_adult_3,
};
static const Icon* dragon_adult_sleeping_frames[] = {
    &I_dragon_adult_sleeping_0,
    &I_dragon_adult_sleeping_1,
    &I_dragon_adult_sleeping_2,
    &I_dragon_adult_sleeping_3,
};

static const Icon* dragon_pet_frames[] = {
    &I_dragon_pet_animation_0,
    &I_dragon_pet_animation_1,
    &I_dragon_pet_animation_2,
    &I_dragon_pet_animation_3,
    &I_dragon_pet_animation_4,
    &I_dragon_pet_animation_5,
    &I_dragon_pet_animation_6,
    &I_dragon_pet_animation_7,
};

// RABBIT

static const Icon* rabbit_baby_frames[] = {
    &I_rabbit_baby_0,
    &I_rabbit_baby_1,
    &I_rabbit_baby_2,
    &I_rabbit_baby_3,
};
static const Icon* rabbit_baby_sleeping_frames[] = {
    &I_rabbit_baby_sleeping_0,
    &I_rabbit_baby_sleeping_1,
    &I_rabbit_baby_sleeping_2,
    &I_rabbit_baby_sleeping_3,
};

static const Icon* rabbit_teen_frames[] = {
    &I_rabbit_teen_0,
    &I_rabbit_teen_1,
    &I_rabbit_teen_2,
    &I_rabbit_teen_3,
};
static const Icon* rabbit_teen_sleeping_frames[] = {
    &I_rabbit_teen_sleeping_0,
    &I_rabbit_teen_sleeping_1,
    &I_rabbit_teen_sleeping_2,
    &I_rabbit_teen_sleeping_3,
};

static const Icon* rabbit_adult_frames[] = {
    &I_rabbit_adult_0,
    &I_rabbit_adult_1,
    &I_rabbit_adult_2,
    &I_rabbit_adult_3,
};
static const Icon* rabbit_adult_sleeping_frames[] = {
    &I_rabbit_adult_sleeping_0,
    &I_rabbit_adult_sleeping_1,
    &I_rabbit_adult_sleeping_2,
    &I_rabbit_adult_sleeping_3,
};

static const Icon* rabbit_pet_frames[] = {
    &I_rabbit_pet_animation_0,
    &I_rabbit_pet_animation_1,
    &I_rabbit_pet_animation_2,
    &I_rabbit_pet_animation_3,
    &I_rabbit_pet_animation_4,
    &I_rabbit_pet_animation_5,
    &I_rabbit_pet_animation_6,
    &I_rabbit_pet_animation_7,
};

// TURTLE

static const Icon* turtle_baby_frames[] = {
    &I_turtle_baby_0,
    &I_turtle_baby_1,
    &I_turtle_baby_2,
    &I_turtle_baby_3,
};
static const Icon* turtle_baby_sleeping_frames[] = {
    &I_turtle_baby_sleeping_0,
    &I_turtle_baby_sleeping_1,
    &I_turtle_baby_sleeping_2,
    &I_turtle_baby_sleeping_3,
};

static const Icon* turtle_teen_frames[] = {
    &I_turtle_teen_0,
    &I_turtle_teen_1,
    &I_turtle_teen_2,
    &I_turtle_teen_3,
};
static const Icon* turtle_teen_sleeping_frames[] = {
    &I_turtle_teen_sleeping_0,
    &I_turtle_teen_sleeping_1,
    &I_turtle_teen_sleeping_2,
    &I_turtle_teen_sleeping_3,
};

static const Icon* turtle_adult_frames[] = {
    &I_turtle_adult_0,
    &I_turtle_adult_1,
    &I_turtle_adult_2,
    &I_turtle_adult_3,
};
static const Icon* turtle_adult_sleeping_frames[] = {
    &I_turtle_adult_sleeping_0,
    &I_turtle_adult_sleeping_1,
    &I_turtle_adult_sleeping_2,
    &I_turtle_adult_sleeping_3,
};

static const Icon* turtle_pet_frames[] = {
    &I_turtle_pet_animation_0,
    &I_turtle_pet_animation_1,
    &I_turtle_pet_animation_2,
    &I_turtle_pet_animation_3,
    &I_turtle_pet_animation_4,
    &I_turtle_pet_animation_5,
    &I_turtle_pet_animation_6,
    &I_turtle_pet_animation_7,
};

// ANIMATIONS

static const Icon* full_frames[] = {
    &I_full_animation_0,
    &I_full_animation_1,
    &I_full_animation_2,
    &I_full_animation_3,
    &I_full_animation_4,
    &I_full_animation_5,
    &I_full_animation_6,
    &I_full_animation_7,
};
static const Icon* sleep_frames[] = {
    &I_sleep_animation_0,
    &I_sleep_animation_1,
    &I_sleep_animation_2,
    &I_sleep_animation_3,
    &I_sleep_animation_4,
    &I_sleep_animation_5,
    &I_sleep_animation_6,
    &I_sleep_animation_7,
};

// ZerogotchiAnimation animation;

void draw_callback(Canvas* canvas, void* ctx) {
    AppContext* app = ctx;

    canvas_clear(canvas);

    char str[64];

    // Pet

    if(!app->animation.is_animating) {
        switch(app->game_stats.type) {
        case(DOLPHIN):
            switch(app->game_stats.stage) {
            case(BABY):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        48,
                        20,
                        dolphin_baby_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 48, 20, dolphin_baby_frames[app->animation.animation_frame]);
                break;
            case(TEEN):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        48,
                        13,
                        dolphin_teen_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 48, 13, dolphin_teen_frames[app->animation.animation_frame]);
                break;
            case(ADULT):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        42,
                        8,
                        dolphin_adult_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 42, 8, dolphin_adult_frames[app->animation.animation_frame]);
                break;
            default:
                break;
            }
            break;
        case(DRAGON):
            switch(app->game_stats.stage) {
            case(BABY):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        50,
                        18,
                        dragon_baby_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 50, 18, dragon_baby_frames[app->animation.animation_frame]);
                break;
            case(TEEN):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        46,
                        16,
                        dragon_teen_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 46, 16, dragon_teen_frames[app->animation.animation_frame]);
                break;
            case(ADULT):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        40,
                        8,
                        dragon_adult_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 40, 8, dragon_adult_frames[app->animation.animation_frame]);
                break;
            default:
                break;
            }
            break;
        case(RABBIT):
            switch(app->game_stats.stage) {
            case(BABY):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        52,
                        20,
                        rabbit_baby_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 52, 20, rabbit_baby_frames[app->animation.animation_frame]);
                break;
            case(TEEN):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        50,
                        14,
                        rabbit_teen_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 50, 14, rabbit_teen_frames[app->animation.animation_frame]);
                break;
            case(ADULT):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        46,
                        10,
                        rabbit_adult_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 46, 10, rabbit_adult_frames[app->animation.animation_frame]);
                break;
            default:
                break;
            }
            break;
        case(TURTLE):
            switch(app->game_stats.stage) {
            case(BABY):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        52,
                        20,
                        turtle_baby_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 50, 20, turtle_baby_frames[app->animation.animation_frame]);
                break;
            case(TEEN):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        48,
                        22,
                        turtle_teen_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 49, 22, turtle_teen_frames[app->animation.animation_frame]);
                break;
            case(ADULT):
                if(app->game_stats.is_sleeping)
                    canvas_draw_icon(
                        canvas,
                        40,
                        15,
                        turtle_adult_sleeping_frames[app->animation.animation_frame]);
                else
                    canvas_draw_icon(
                        canvas, 40, 15, turtle_adult_frames[app->animation.animation_frame]);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    // Stats

    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 10, NAME);

    canvas_set_font(canvas, FontSecondary);
    snprintf(str, sizeof(str), "lvl %ld", app->game_stats.lvl);
    canvas_draw_str(canvas, 3, 19, str);

    canvas_draw_icon(canvas, 87, 2, &I_stats);

    canvas_draw_box(canvas, 95 + (30 - app->game_stats.health), 3, app->game_stats.health, 4);
    canvas_draw_box(
        canvas, 95 + (30 - app->game_stats.happiness), 10, app->game_stats.happiness, 4);
    canvas_draw_box(canvas, 95 + (30 - app->game_stats.hunger), 17, app->game_stats.hunger, 4);

    // Actions

    canvas_draw_icon(canvas, 4, 50, &I_eat);
    canvas_draw_icon(canvas, 22, 50, &I_pet);
    canvas_draw_icon(canvas, 40, 50, &I_play);
    canvas_draw_icon(canvas, 58, 50, &I_sleep);
    canvas_draw_icon(canvas, 76, 50, &I_heal);
    canvas_draw_icon(canvas, 94, 50, &I_info);
    canvas_draw_icon(canvas, 112, 50, &I_settings);

    switch(app->selectedAction) {
    case 0:
        canvas_draw_icon(canvas, 3, 49, &I_eat_hover);
        break;
    case 1:
        canvas_draw_icon(canvas, 21, 49, &I_pet_hover);
        break;
    case 2:
        canvas_draw_icon(canvas, 39, 49, &I_play_hover);
        break;
    case 3:
        canvas_draw_icon(canvas, 57, 49, &I_sleep_hover);
        break;
    case 4:
        canvas_draw_icon(canvas, 75, 49, &I_heal_hover);
        break;
    case 5:
        canvas_draw_icon(canvas, 93, 49, &I_info_hover);
        break;
    case 6:
        canvas_draw_icon(canvas, 111, 49, &I_settings_hover);
        break;
    default:
        break;
    }

    // Scenes

    switch(app->action) {
    case eating:
        draw_eat_scene(canvas, app->current_y, app->game_stats.type);
        break;
    case playing:
        draw_play_scene(canvas, app->current_y);
        break;
    case game_TicTacToe:
        draw_game_TicTacToe(canvas);
        break;
    case game_NoSignal:
        draw_game_NoSignal(canvas, app);
        break;
    case game_Memory:
        draw_game_Memory(canvas);
        break;
    case going_to_sleep:
        draw_going_to_sleep_scene(canvas, app->current_x);
        break;
    case sleeping:
        draw_sleep_scene(canvas, app);
        break;
    case waking_up:
        draw_wake_up_scene(canvas, app->current_y);
        break;
    case healing:
        draw_heal_scene(canvas, app->current_y);
        break;
    case informing:
        draw_info_scene(canvas, app);
        break;
    case in_settings:
        draw_settings_screen(canvas, app->current_y);
        break;
    case reset:
        draw_reset_screen(canvas, app->current_y);
        break;
    case pet_selection:
        draw_pet_selection_screen(canvas, app);
        break;
    default:
        break;
    }

    // Animations

    if(app->animation.is_animating) {
        switch(app->game_stats.type) {
        case(DOLPHIN):
            if(app->selectedAction == eat)
                canvas_draw_icon(canvas, 0, 0, full_frames[app->animation.animation_frame]);
            else if(app->selectedAction == pet)
                canvas_draw_icon(canvas, 0, 0, dolphin_pet_frames[app->animation.animation_frame]);
            else if(app->selectedAction == sleep) {
                canvas_draw_icon(canvas, 0, 0, sleep_frames[app->animation.animation_frame]);
            }
            break;
        case(DRAGON):
            if(app->selectedAction == eat)
                canvas_draw_icon(canvas, 0, 0, full_frames[app->animation.animation_frame]);
            else if(app->selectedAction == pet)
                canvas_draw_icon(canvas, 0, 0, dragon_pet_frames[app->animation.animation_frame]);
            else if(app->selectedAction == sleep) {
                canvas_draw_icon(canvas, 0, 0, sleep_frames[app->animation.animation_frame]);
            }
            break;
        case(RABBIT):
            if(app->selectedAction == eat)
                canvas_draw_icon(canvas, 0, 0, full_frames[app->animation.animation_frame]);
            else if(app->selectedAction == pet)
                canvas_draw_icon(canvas, 0, 0, rabbit_pet_frames[app->animation.animation_frame]);
            else if(app->selectedAction == sleep) {
                canvas_draw_icon(canvas, 0, 0, sleep_frames[app->animation.animation_frame]);
            }
            break;
        case(TURTLE):
            if(app->selectedAction == eat)
                canvas_draw_icon(canvas, 0, 0, full_frames[app->animation.animation_frame]);
            else if(app->selectedAction == pet)
                canvas_draw_icon(canvas, 0, 0, turtle_pet_frames[app->animation.animation_frame]);
            else if(app->selectedAction == sleep) {
                canvas_draw_icon(canvas, 0, 0, sleep_frames[app->animation.animation_frame]);
            }
            break;
        default:
            break;
        }
    }
}
