#include "info_scene.h"

void draw_info_scene(Canvas* canvas, AppContext* app) {
    char str[64];
    canvas_clear(canvas);

    switch(app->game_stats.type) {
    case(DOLPHIN):
        if(app->game_stats.is_sleeping)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dolphin_sleep);
        else if(app->game_stats.health < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dolphin_ill);
        else if(app->game_stats.hunger < 10 || app->game_stats.happiness < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dolphin_sad);
        else
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dolphin_happy);
        break;
    case(DRAGON):
        if(app->game_stats.is_sleeping)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dragon_sleep);
        else if(app->game_stats.health < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dragon_ill);
        else if(app->game_stats.hunger < 10 || app->game_stats.happiness < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dragon_sad);
        else
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_dragon_happy);
        break;
    case(RABBIT):
        if(app->game_stats.is_sleeping)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_rabbit_sleep);
        else if(app->game_stats.health < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_rabbit_ill);
        else if(app->game_stats.hunger < 10 || app->game_stats.happiness < 10)
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_rabbit_sad);
        else
            canvas_draw_icon(canvas, ASSET_X, ASSET_Y, &I_rabbit_happy);
        break;
    default:
        break;
    }

    canvas_set_font(canvas, FontPrimary);
    snprintf(str, sizeof(str), "%s | lvl %ld", NAME, app->game_stats.lvl);
    canvas_draw_str(canvas, 6, 14, str);

    // Stats

    canvas_set_font(canvas, FontSecondary);

    snprintf(
        str,
        sizeof(str),
        "exp: %ld/%d",
        app->game_stats.exp,
        (int)pow(app->game_stats.lvl + 1, 2) * 10);
    canvas_draw_str(canvas, 8, 24, str);

    snprintf(str, sizeof(str), "health: %ld/30", app->game_stats.health);
    canvas_draw_str(canvas, 8, 40, str);

    snprintf(str, sizeof(str), "happiness: %ld/30", app->game_stats.happiness);
    canvas_draw_str(canvas, 8, 49, str);

    snprintf(str, sizeof(str), "hunger: %ld/30", app->game_stats.hunger);
    canvas_draw_str(canvas, 8, 58, str);

    // canvas_draw_str(canvas, 8, 32, "sec:");
    // snprintf(str, sizeof(str), "%ld", seconds_passed_here);
    // canvas_draw_str(canvas, 26, 32, str);
}
