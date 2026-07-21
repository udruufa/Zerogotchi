#pragma once

#include <gui/elements.h>

#include "../app_structs.h"
#include "../stats.h"

void init_new_game_Memory();
void handle_input_game_Memory(ZerogotchiEvent* event, AppContext* app);
void draw_game_Memory(Canvas* canvas);
