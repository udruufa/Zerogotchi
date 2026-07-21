#include "timer.h"

void timer_callback(void* ctx) {
    furi_assert(ctx);
    AppContext* app = ctx;

    ZerogotchiEvent event = {.type = EventTypeTick};
    furi_message_queue_put(app->event_queue, &event, 0);

    if(!app->animation.is_animating) {
        app->animation.animation_frame++;
        if(app->animation.animation_frame >= app->animation.frames) {
            app->animation.animation_frame = 0;
        }
    }

    if(app->game_stats.is_sleeping) {
        if(app->game_stats.sleep_time > 0) {
            app->game_stats.sleep_time--;
        } else if(app->game_stats.sleep_time == 0) {
            add_exp(10, app);
            increase_stat(&app->game_stats.health, 12); //health +12
            increase_stat(&app->game_stats.happiness, 12); //happiness +12
            decrease_stat(&app->game_stats.hunger, 5); //hunger -5
            app->animation.is_animating = false;
            app->game_stats.is_sleeping = false;
            app->action = NONE;
        }
    }
}

void animation_timer_callback(void* ctx) {
    furi_assert(ctx);
    AppContext* app = ctx;

    if(app->animation.is_animating) {
        app->animation.animation_frame++;
        if(app->animation.animation_frame >= app->animation.frames) {
            if(app->action == game_NoSignal) {
                app->animation.frames = 2;
                app->animation.animation_frame = 0;
            } else {
                app->animation.is_animating = false;
                app->animation.frames = 4;
                app->animation.animation_frame = 0;
                if(app->selectedAction == sleep) {
                    app->action = going_to_sleep;
                    app->current_x = GO_TO_SLEEP_YES_X;
                }
            }
        }
    }
}

void handle_offline_timer(AppContext* app) {
    uint32_t now = furi_hal_rtc_get_timestamp();
    uint32_t seconds_passed = now - app->game_stats.last_save_time;
    if(now < app->game_stats.last_save_time) {
        seconds_passed = 0;
    }

    if(app->game_stats.health > seconds_passed / app->game_stats.health_time)
        app->game_stats.health -= seconds_passed / app->game_stats.health_time;
    else
        app->game_stats.health = 0;

    if(app->game_stats.happiness > seconds_passed / app->game_stats.happiness_time)
        app->game_stats.happiness -= seconds_passed / app->game_stats.happiness_time;
    else
        app->game_stats.happiness = 0;

    if(app->game_stats.hunger > seconds_passed / app->game_stats.hunger_time)
        app->game_stats.hunger -= seconds_passed / app->game_stats.hunger_time;
    else
        app->game_stats.hunger = 0;

    if(app->game_stats.is_sleeping) {
        app->game_stats.sleep_time -= seconds_passed;
    }
}

void handle_timer(AppContext* app) {
    uint32_t now = furi_hal_rtc_get_timestamp();
    uint32_t seconds_passed_here = now - app->game_stats.load_time;
    if(now < app->game_stats.load_time) {
        seconds_passed_here = 0;
    }

    if(app->game_stats.health > 0 && seconds_passed_here % app->game_stats.health_time == 0 &&
       seconds_passed_here >= app->game_stats.health_time && app->game_stats.stage == ADULT) {
        app->game_stats.health--;
    }
    if(app->game_stats.happiness > 0 &&
       seconds_passed_here % app->game_stats.happiness_time == 0 &&
       seconds_passed_here >= app->game_stats.happiness_time) {
        app->game_stats.happiness--;
    }
    if(app->game_stats.hunger > 0 && seconds_passed_here % app->game_stats.hunger_time == 0 &&
       seconds_passed_here >= app->game_stats.hunger_time) {
        app->game_stats.hunger--;
    }
    if(seconds_passed_here % app->game_stats.exp_time == 0) {
        add_exp(1, app);
    }

    if(app->game_stats.happiness == 0) {
        app->game_stats.health_time = HEALTH_TIME_BABY_0_HAPPINESS;
    }
    if(app->game_stats.hunger == 0) {
        app->game_stats.health_time = HEALTH_TIME_BABY_0_HUNGER;
        app->game_stats.happiness_time = HAPPINESS_TIME_BABY_0_HUNGER;
    }
}
