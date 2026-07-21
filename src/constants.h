#pragma once

#include <furi_hal.h>

#define SAVE_PATH APP_DATA_PATH("zerogotchi.save")

#define NAME strchr(furi_hal_version_get_ble_local_device_name_ptr(), ' ') + 1

#define LVL_TEEN  5
#define LVL_ADULT 9

#define MAX_STAT 30U

#define HEALTH_TIME_BABY             0
#define HEALTH_TIME_BABY_0_HAPPINESS 20
#define HEALTH_TIME_BABY_0_HUNGER    40
#define HAPPINESS_TIME_BABY          60
#define HAPPINESS_TIME_BABY_0_HUNGER 90
#define HUNGER_TIME_BABY             30
#define EXP_TIME_BABY                30

#define HEALTH_TIME_TEEN    0
#define HAPPINESS_TIME_TEEN 120
#define HUNGER_TIME_TEEN    100
#define EXP_TIME_TEEN       120

#define HEALTH_TIME_ADULT    7200
#define HAPPINESS_TIME_ADULT 4800
#define HUNGER_TIME_ADULT    3600
#define EXP_TIME_ADULT       14400

#define CHOICE_SCENE_X 48

#define FOOD_SARDINE_Y  8
#define FOOD_SQUID_Y    20
#define FOOD_MACKEREL_Y 32
#define FOOD_ICEFISH_Y  48

#define GAMES_TICTACTOE_Y 16
#define GAMES_NOSIGNAL_Y  28
#define GAMES_MEMORY_Y    40

#define GO_TO_SLEEP_YES_X 35
#define GO_TO_SLEEP_NO_X  93

#define WAKE_UP_SURE_Y 14
#define WAKE_UP_YES_Y  30
#define WAKE_UP_NO_Y   42

#define MEDICINES_VITAMINS_Y  16
#define MEDICINES_PILLS_Y     28
#define MEDICINES_INJECTION_Y 40
