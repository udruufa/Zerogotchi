#pragma once

#include "constants.h"
#include "app_structs.h"

void add_exp(uint32_t value, AppContext* app);
void increase_stat(uint32_t* stat, uint32_t value);
void decrease_stat(uint32_t* stat, uint32_t value);
