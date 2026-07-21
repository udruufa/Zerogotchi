#pragma once

#include <gui/elements.h>

#include "../../constants.h"
#include "../../app_structs.h"

void draw_going_to_sleep_scene(Canvas* canvas, uint32_t current_x);
void draw_sleep_scene(Canvas* canvas, AppContext* app);
void draw_wake_up_scene(Canvas* canvas, uint32_t current_y);
