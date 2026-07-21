#pragma once

#include <gui/elements.h>

#include "../app_structs.h"
#include "../stats.h"

#define JUMP_SPEED 12

void init_new_game_NoSignal();
void handle_input_game_NoSignal(ZerogotchiEvent* event, AppContext* app);
void draw_game_NoSignal(Canvas* canvas, AppContext* app);
