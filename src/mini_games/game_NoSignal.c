#include "game_NoSignal.h"
#include "../feedback.h"

static const Icon* dolphin_idle_frames[] = {
    &I_dolphin_idle_0,
    &I_dolphin_idle_1,
};
static const Icon* dragon_idle_frames[] = {
    &I_dragon_idle_0,
    &I_dragon_idle_1,
};
static const Icon* rabbit_idle_frames[] = {
    &I_rabbit_idle_0,
    &I_rabbit_idle_1,
};
static const Icon* turtle_idle_frames[] = {
    &I_turtle_idle_0,
    &I_turtle_idle_1,
};

static const Icon* dolphin_blocks[] = {
    &I_dolphin_block_1,
    &I_dolphin_block_2,
    &I_dolphin_block_3,
};
static const Icon* dragon_blocks[] = {
    &I_dragon_block_1,
    &I_dragon_block_2,
    &I_dragon_block_3,
};
static const Icon* rabbit_blocks[] = {
    &I_rabbit_block_1,
    &I_rabbit_block_2,
    &I_rabbit_block_3,
};
static const Icon* turtle_blocks[] = {
    &I_turtle_block_1,
    &I_turtle_block_2,
    &I_turtle_block_3,
};

static int32_t ground_x;
static uint32_t block_timer;
static int32_t (*blocks_on_screen)[4] = NULL; //left
static size_t rows = 0;

static bool is_jump;
static int32_t jump_y;
static int32_t jump_speed = JUMP_SPEED;

static bool is_end;

static uint32_t nosignal_last_update;

void init_new_game_NoSignal() {
    ground_x = 0;
    block_timer = 1;
    free(blocks_on_screen);
    blocks_on_screen = NULL;
    rows = 0;

    is_jump = false;
    jump_y = 32;
    jump_speed = JUMP_SPEED;

    is_end = false;

    nosignal_last_update = 0;
}

void handle_input_game_NoSignal(ZerogotchiEvent* event, AppContext* app) {
    if(event->input.key == InputKeyBack) {
        app->action = playing;
        app->animation.is_animating = false;
        app->animation.frames = 4;
        app->animation.animation_frame = 0;
    } else if(event->input.key == InputKeyOk) {
        if(is_end) {
            add_exp(3, app);
            increase_stat(&app->game_stats.happiness, 3); //happiness +3
            decrease_stat(&app->game_stats.hunger, 2); //hunger -2
            init_new_game_NoSignal();
            is_end = false;
        } else {
            if(!is_jump) {
                is_jump = true;
            }
        }
    }
}

void update_NoSignal(AppContext* app) {
    const uint32_t update_period = 250;
    uint32_t now = furi_get_tick();

    if(nosignal_last_update == 0) {
        nosignal_last_update = now;
        return;
    }
    if(now - nosignal_last_update < update_period) {
        return;
    }
    nosignal_last_update += update_period;

    if(!block_timer) {
        block_timer = rand() % 10 + 8;
        uint32_t block = rand() % 3;

        rows++;
        blocks_on_screen = realloc(blocks_on_screen, rows * sizeof(*blocks_on_screen));

        blocks_on_screen[rows - 1][0] = 128;
        blocks_on_screen[rows - 1][1] = block;
        switch(block) {
        case 0:
            switch(app->game_stats.type) {
            case(DOLPHIN):
                blocks_on_screen[rows - 1][2] = 7;
                blocks_on_screen[rows - 1][3] = 31;
                break;
            case(DRAGON):
                blocks_on_screen[rows - 1][2] = 17;
                blocks_on_screen[rows - 1][3] = 34;
                break;
            case(RABBIT):
                blocks_on_screen[rows - 1][2] = 11;
                blocks_on_screen[rows - 1][3] = 31;
                break;
            case(TURTLE):
                blocks_on_screen[rows - 1][2] = 11;
                blocks_on_screen[rows - 1][3] = 31;
                break;
            default:
                break;
            }
            break;
        case 1:
            switch(app->game_stats.type) {
            case(DOLPHIN):
                blocks_on_screen[rows - 1][2] = 16;
                blocks_on_screen[rows - 1][3] = 29;
                break;
            case(DRAGON):
                blocks_on_screen[rows - 1][2] = 18;
                blocks_on_screen[rows - 1][3] = 29;
                break;
            case(RABBIT):
                blocks_on_screen[rows - 1][2] = 15;
                blocks_on_screen[rows - 1][3] = 34;
                break;
            case(TURTLE):
                blocks_on_screen[rows - 1][2] = 16;
                blocks_on_screen[rows - 1][3] = 28;
                break;
            default:
                break;
            }
            break;
        case 2:
            switch(app->game_stats.type) {
            case(DOLPHIN):
                blocks_on_screen[rows - 1][2] = 24;
                blocks_on_screen[rows - 1][3] = 28;
                break;
            case(DRAGON):
                blocks_on_screen[rows - 1][2] = 22;
                blocks_on_screen[rows - 1][3] = 32;
                break;
            case(RABBIT):
                blocks_on_screen[rows - 1][2] = 22;
                blocks_on_screen[rows - 1][3] = 33;
                break;
            case(TURTLE):
                blocks_on_screen[rows - 1][2] = 22;
                blocks_on_screen[rows - 1][3] = 33;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    for(uint32_t i = 0; i < rows; i++) {
        blocks_on_screen[i][0] -= 8;
    }

    if(rows && blocks_on_screen[0][0] <= -30) {
        rows--;
        memmove(&blocks_on_screen[0], &blocks_on_screen[1], (rows) * sizeof(*blocks_on_screen));
        if(rows == 0) {
            free(blocks_on_screen);
            blocks_on_screen = NULL;
        } else {
            int32_t (*temp)[4] = realloc(blocks_on_screen, rows * sizeof(*blocks_on_screen));
            if(temp != NULL) {
                blocks_on_screen = temp;
            }
        }
    }

    if(is_jump) {
        jump_y -= jump_speed;
        jump_speed -= 4;
        if(jump_y == 32) {
            jump_speed = JUMP_SPEED;
            is_jump = false;
        }
    }

    if(ground_x >= -128) {
        ground_x--;
    } else {
        ground_x = 0;
    }

    block_timer--;

    if(rows && blocks_on_screen[0][0] <= 24 &&
       blocks_on_screen[0][0] + blocks_on_screen[0][2] >= 11 &&
       (jump_y > blocks_on_screen[0][3] ||
        (jump_speed < 0 && jump_y + 13 >= blocks_on_screen[0][3]))) {
        is_end = true;
        if(app->game_stats.sound_on && !app->feedbacked) {
            app->sound = END;
            feedback_sound(app);
            app->feedbacked = true;
        }
    }
}

void draw_game_NoSignal(Canvas* canvas, AppContext* app) {
    canvas_clear(canvas);

    if(is_end) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "THE END");
        return;
    }

    switch(app->game_stats.type) {
    case(DOLPHIN):
        canvas_draw_icon(canvas, ground_x, 48, &I_dolphin_ground);
        canvas_draw_icon(canvas, ground_x + 128, 48, &I_dolphin_ground);

        for(uint32_t i = 0; i < rows; i++) {
            canvas_draw_icon(
                canvas,
                blocks_on_screen[i][0],
                blocks_on_screen[i][3],
                dolphin_blocks[blocks_on_screen[i][1]]);
        }

        if(is_jump) {
            canvas_draw_icon(canvas, 11, jump_y, &I_dolphin_jump);
        } else {
            canvas_draw_icon(canvas, 11, 32, dolphin_idle_frames[app->animation.animation_frame]);
        }

        break;
    case(DRAGON):
        canvas_draw_icon(canvas, ground_x, 48, &I_dragon_ground);
        canvas_draw_icon(canvas, ground_x + 128, 48, &I_dragon_ground);

        for(uint32_t i = 0; i < rows; i++) {
            canvas_draw_icon(
                canvas,
                blocks_on_screen[i][0],
                blocks_on_screen[i][3],
                dragon_blocks[blocks_on_screen[i][1]]);
        }

        if(is_jump) {
            canvas_draw_icon(canvas, 11, jump_y, &I_dragon_jump);
        } else {
            canvas_draw_icon(canvas, 11, 30, dragon_idle_frames[app->animation.animation_frame]);
        }

        break;
    case(RABBIT):
        canvas_draw_icon(canvas, ground_x, 48, &I_rabbit_ground);
        canvas_draw_icon(canvas, ground_x + 128, 48, &I_rabbit_ground);

        for(uint32_t i = 0; i < rows; i++) {
            canvas_draw_icon(
                canvas,
                blocks_on_screen[i][0],
                blocks_on_screen[i][3],
                rabbit_blocks[blocks_on_screen[i][1]]);
        }

        if(is_jump) {
            canvas_draw_icon(canvas, 11, jump_y, &I_rabbit_jump);
        } else {
            canvas_draw_icon(canvas, 11, 36, rabbit_idle_frames[app->animation.animation_frame]);
        }

        break;
    case(TURTLE):
        canvas_draw_icon(canvas, ground_x, 48, &I_turtle_ground);
        canvas_draw_icon(canvas, ground_x + 128, 48, &I_turtle_ground);

        for(uint32_t i = 0; i < rows; i++) {
            canvas_draw_icon(
                canvas,
                blocks_on_screen[i][0],
                blocks_on_screen[i][3],
                turtle_blocks[blocks_on_screen[i][1]]);
        }

        if(is_jump) {
            canvas_draw_icon(canvas, 11, jump_y, &I_turtle_jump);
        } else {
            canvas_draw_icon(canvas, 11, 37, turtle_idle_frames[app->animation.animation_frame]);
        }

        break;
    default:
        break;
    }
}
