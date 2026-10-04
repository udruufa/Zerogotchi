#pragma once

#include <input/input.h>
#include <zerogotchi_icons.h>

typedef enum {
    DOLPHIN,
    DRAGON,
    RABBIT,
    TURTLE,
    COUNT_TYPE
} ZerogotchiType;

typedef enum {
    BABY,
    TEEN,
    ADULT
} ZerogotchiStage;

typedef struct {
    ZerogotchiType type;
    ZerogotchiStage stage;

    uint32_t health;
    uint32_t happiness;
    uint32_t hunger;

    uint32_t exp;
    uint32_t lvl;

    uint32_t health_time;
    uint32_t happiness_time;
    uint32_t hunger_time;
    uint32_t exp_time;

    bool is_sleeping;
    uint32_t sleep_time;

    uint32_t last_save_time;
    uint32_t load_time;
} ZerogotchiStats;

typedef enum {
    eat,
    pet,
    play,
    sleep,
    heal,
    info,
    COUNT_ACTION
} ZerogotchiSelectAction;

typedef enum {
    NONE,
    eating,
    petting,
    playing,
    game_TicTacToe,
    game_NoSignal,
    game_Memory,
    going_to_sleep,
    sleeping,
    waking_up,
    healing,
    informing,
    menu,
    settings,
    pet_selection
} ZerogotchiAction;

typedef struct {
    bool is_animating;
    uint32_t frames;
    uint32_t animation_frame;
} ZerogotchiAnimation;

typedef enum {
    EventTypeTick,
    EventTypeInput
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} ZerogotchiEvent;
