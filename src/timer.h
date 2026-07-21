#pragma once

#include "stats.h"

void timer_callback(void* ctx);
void animation_timer_callback(void* ctx);
void handle_offline_timer(AppContext* app);
void handle_timer(AppContext* app);
