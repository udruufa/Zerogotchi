#pragma once

#include <gui/elements.h>

#include "../app_structs.h"
#include "../stats.h"

#define X1 40
#define X2 57
#define X3 74

#define Y1 8
#define Y2 25
#define Y3 42

#define MOVEMENT 17

void init_new_game_TicTacToe();
void handle_input_game_TicTacToe(ZerogotchiEvent* event, AppContext* app);
void draw_game_TicTacToe(Canvas* canvas, AppContext* app);
