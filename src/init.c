#include "init.h"

void init_new_game(AppContext* app) {
    app->game_stats.health = MAX_STAT;
    app->game_stats.happiness = MAX_STAT;
    app->game_stats.hunger = MAX_STAT;
    app->game_stats.exp = 0;
    app->game_stats.lvl = 1;
    app->game_stats.health_time = HEALTH_TIME_BABY;
    app->game_stats.happiness_time = HAPPINESS_TIME_BABY;
    app->game_stats.hunger_time = HUNGER_TIME_BABY;
    app->game_stats.exp_time = EXP_TIME_BABY;
    app->game_stats.is_sleeping = false;

    app->game_stats.last_save_time = furi_hal_rtc_get_timestamp();
    app->game_stats.load_time = furi_hal_rtc_get_timestamp();
}
