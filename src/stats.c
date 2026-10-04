#include "stats.h"

void add_exp(uint32_t value, AppContext* app) {
    app->game_stats.exp += value;
    if(app->game_stats.exp >= pow((app->game_stats.lvl + 1), 2) * 10) {
        app->game_stats.lvl++;
        app->game_stats.exp = 0;
    }

    if(app->game_stats.lvl >= LVL_ADULT) {
        app->game_stats.stage = ADULT;
        app->game_stats.health_time = HEALTH_TIME_ADULT;
        app->game_stats.happiness_time = HAPPINESS_TIME_ADULT;
        app->game_stats.hunger_time = HUNGER_TIME_ADULT;
    } else if(app->game_stats.lvl >= LVL_TEEN) {
        app->game_stats.stage = TEEN;
        app->game_stats.health_time = HEALTH_TIME_TEEN;
        app->game_stats.happiness_time = HAPPINESS_TIME_TEEN;
        app->game_stats.hunger_time = HUNGER_TIME_TEEN;
    } else {
        app->game_stats.stage = BABY;
    }
}

void increase_stat(uint32_t* stat, uint32_t value) {
    *stat = MIN(MAX_STAT, *stat + value);
}

void decrease_stat(uint32_t* stat, uint32_t value) {
    *stat = MAX(value, *stat) - value;
}
