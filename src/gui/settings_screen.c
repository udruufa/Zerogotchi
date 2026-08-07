#include "settings_screen.h"

static const Icon* dolphin_baby_frames[] = {
    &I_dolphin_baby_0,
    &I_dolphin_baby_1,
    &I_dolphin_baby_2,
    &I_dolphin_baby_3,
};
static const Icon* dragon_baby_frames[] = {
    &I_dragon_baby_0,
    &I_dragon_baby_1,
    &I_dragon_baby_2,
    &I_dragon_baby_3,
};
static const Icon* rabbit_baby_frames[] = {
    &I_rabbit_baby_0,
    &I_rabbit_baby_1,
    &I_rabbit_baby_2,
    &I_rabbit_baby_3,
};

void draw_settings_screen(Canvas* canvas, void* ctx) {
    AppContext* app = ctx;

    canvas_clear(canvas);

    canvas_draw_icon(canvas, 16, 6, &I_pet_selection_title);
    elements_multiline_text_aligned(canvas, 36, 52, AlignLeft, AlignCenter, "<");
    elements_multiline_text_aligned(canvas, 89, 52, AlignLeft, AlignCenter, ">");

    switch(app->game_stats.type) {
    case(DOLPHIN):
        elements_multiline_text_aligned(canvas, 64, 52, AlignCenter, AlignCenter, "Dolphin");
        canvas_draw_icon(canvas, 48, 22, dolphin_baby_frames[app->animation.animation_frame]);
        break;
    case(DRAGON):
        elements_multiline_text_aligned(canvas, 64, 52, AlignCenter, AlignCenter, "Dragon");
        canvas_draw_icon(canvas, 50, 21, dragon_baby_frames[app->animation.animation_frame]);
        break;
    case(RABBIT):
        elements_multiline_text_aligned(canvas, 64, 52, AlignCenter, AlignCenter, "Rabbit");
        canvas_draw_icon(canvas, 52, 20, rabbit_baby_frames[app->animation.animation_frame]);
        break;
    default:
        break;
    }
}
