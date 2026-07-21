#include "stats.h"

void add_exp(uint32_t value, AppContext* app) {
    app->game_stats.exp += value;
    if(app->game_stats.exp > 10) app->game_stats.lvl = floor(sqrt(app->game_stats.exp / 10));
}

void increase_stat(uint32_t* stat, uint32_t value) {
    *stat = MIN(MAX_STAT, *stat + value);
}

void decrease_stat(uint32_t* stat, uint32_t value) {
    *stat = MAX(value, *stat) - value;
}
