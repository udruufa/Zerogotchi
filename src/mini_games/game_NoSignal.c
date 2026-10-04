#include "game_NoSignal.h"

static const Icon* idle_frames[] = {
    &I_dolphin_idle_0,
    &I_dolphin_idle_1,
};

static const Icon* blocks[] = {
    &I_dolphin_block_1,
    &I_dolphin_block_2,
    &I_dolphin_block_3,
};

static int32_t ground_x;
static uint32_t block_timer;
static int32_t (*blocks_on_screen)[4] = NULL; //left
static size_t rows = 0;

static bool is_jump;
static int32_t jump_y;
static int32_t jump_speed = JUMP_SPEED;

static bool is_end;

void init_new_game_NoSignal() {
    ground_x = 0;
    block_timer = 1;
    free(blocks_on_screen);
    blocks_on_screen = NULL;
    rows = 0;

    is_jump = false;
    jump_y = 32;
    jump_speed = JUMP_SPEED;
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

void draw_game_NoSignal(Canvas* canvas, AppContext* app) {
    canvas_clear(canvas);

    if(rows && blocks_on_screen[0][0] <= 24 &&
       blocks_on_screen[0][0] + blocks_on_screen[0][2] >= 11 &&
       (jump_y > blocks_on_screen[0][3] ||
        (jump_speed < 0 && jump_y + 13 >= blocks_on_screen[0][3]))) {
        canvas_clear(canvas);
        canvas_set_font(canvas, FontPrimary);
        elements_multiline_text_aligned(canvas, 64, 32, AlignCenter, AlignCenter, "THE END");
        is_end = true;
    } else {
        canvas_draw_icon(canvas, ground_x, 48, &I_dolphin_ground);
        canvas_draw_icon(canvas, ground_x + 128, 48, &I_dolphin_ground);
        canvas_draw_box(canvas, 0, 48, 128, 1);

        if(!block_timer) {
            block_timer = rand() % 10 + 8;
            uint32_t block = rand() % 3;

            rows++;
            blocks_on_screen = realloc(blocks_on_screen, rows * sizeof(*blocks_on_screen));

            blocks_on_screen[rows - 1][0] = 128;
            blocks_on_screen[rows - 1][1] = block;
            switch(block) {
            case 0:
                blocks_on_screen[rows - 1][2] = 7;
                blocks_on_screen[rows - 1][3] = 31;
                break;
            case 1:
                blocks_on_screen[rows - 1][2] = 16;
                blocks_on_screen[rows - 1][3] = 29;
                break;
            case 2:
                blocks_on_screen[rows - 1][2] = 26;
                blocks_on_screen[rows - 1][3] = 28;
                break;
            default:
                break;
            }
        }

        if(rows && blocks_on_screen[0][0] <= -30) {
            rows--;
            memmove(
                &blocks_on_screen[0], &blocks_on_screen[1], (rows) * sizeof(*blocks_on_screen));
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

        for(uint32_t i = 0; i < rows; i++) {
            canvas_draw_icon(
                canvas,
                blocks_on_screen[i][0],
                blocks_on_screen[i][3],
                blocks[blocks_on_screen[i][1]]);
            blocks_on_screen[i][0] -= 8;
        }

        if(is_jump) {
            jump_y -= jump_speed;
            canvas_draw_icon(canvas, 11, jump_y, &I_dolphin_jump);
            jump_speed -= 4;
            if(jump_y == 32) {
                jump_speed = JUMP_SPEED;
                is_jump = false;
            }
        } else {
            canvas_draw_icon(canvas, 11, 32, idle_frames[app->animation.animation_frame]);
        }

        if(ground_x >= -128) {
            ground_x--;
        } else {
            ground_x = 0;
        }

        block_timer--;
    }
}
