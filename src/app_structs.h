#pragma once

#include <gui/gui.h>

#include "zerogotchi_structs.h"

typedef struct {
    Gui* gui;
    ViewPort* view_port;

    FuriMessageQueue* event_queue;

    FuriTimer* timer;
    FuriTimer* animation_timer;

    ZerogotchiStats game_stats;

    ZerogotchiSelectAction selectedAction;
    ZerogotchiAction action;

    ZerogotchiAnimation animation;

    ZerogotchiSound sound;

    uint32_t current_y;
    uint32_t current_x;

    bool feedbacked;
} AppContext;
