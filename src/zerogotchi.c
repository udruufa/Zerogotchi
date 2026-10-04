#include "constants.h"
#include "storage.h"
#include "input.h"
#include "timer.h"
#include "gui/zerogotchi_view.h"
#include "mini_games/game_TicTacToe.h"
#include "mini_games/game_NoSignal.h"
#include "mini_games/game_Memory.h"

static AppContext app;

static void init_new_game() {
    app.game_stats.health = MAX_STAT;
    app.game_stats.happiness = MAX_STAT;
    app.game_stats.hunger = MAX_STAT;
    app.game_stats.exp = 0;
    app.game_stats.lvl = 1;
    app.game_stats.health_time = HEALTH_TIME_BABY;
    app.game_stats.happiness_time = HAPPINESS_TIME_BABY;
    app.game_stats.hunger_time = HUNGER_TIME_BABY;
    app.game_stats.exp_time = EXP_TIME_BABY;
    app.game_stats.is_sleeping = false;

    app.game_stats.last_save_time = furi_hal_rtc_get_timestamp();
    app.game_stats.load_time = furi_hal_rtc_get_timestamp();

    app.action = in_settings;
}

int32_t zerogotchi_app(void* p) {
    UNUSED(p);

    ZerogotchiEvent event;
    app.event_queue = furi_message_queue_alloc(8, sizeof(ZerogotchiEvent));

    app.view_port = view_port_alloc();
    view_port_draw_callback_set(app.view_port, draw_callback, &app);
    view_port_input_callback_set(app.view_port, input_callback, &app);

    if(!save_file_exists())
        init_new_game();
    else
        load_game(&app);
    app.game_stats.load_time = furi_hal_rtc_get_timestamp();

    app.gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(app.gui, app.view_port, GuiLayerFullscreen);

    app.timer = furi_timer_alloc(timer_callback, FuriTimerTypePeriodic, &app);
    furi_timer_start(app.timer, 1000);
    app.animation_timer = furi_timer_alloc(animation_timer_callback, FuriTimerTypePeriodic, &app);
    furi_timer_start(app.animation_timer, 250);

    app.animation.animation_frame = 0;
    app.animation.frames = 4;

    handle_offline_timer(&app);

    while(1) {
        furi_check(
            furi_message_queue_get(app.event_queue, &event, FuriWaitForever) == FuriStatusOk);
        if(event.type == EventTypeInput && event.input.type == InputTypePress) {
            if(app.action == game_TicTacToe)
                handle_input_game_TicTacToe(&event, &app);
            else if(app.action == game_NoSignal)
                handle_input_game_NoSignal(&event, &app);
            else if(app.action == game_Memory)
                handle_input_game_Memory(&event, &app);
            else if(handle_input(&event, &app))
                break;
        } else if(event.type == EventTypeTick) {
            handle_timer(&app);
        }
    }

    furi_timer_stop(app.timer);
    furi_timer_stop(app.animation_timer);
    furi_timer_free(app.timer);
    furi_timer_free(app.animation_timer);

    furi_message_queue_free(app.event_queue);

    gui_remove_view_port(app.gui, app.view_port);
    view_port_free(app.view_port);
    furi_record_close(RECORD_GUI);

    return 0;
}
