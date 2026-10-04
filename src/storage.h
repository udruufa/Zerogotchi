#pragma once

#include <storage/storage.h>

#include "constants.h"
#include "app_structs.h"

bool save_file_exists(void);
void save_game(AppContext* app);
void load_game(AppContext* app);
