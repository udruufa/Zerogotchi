#include "eat_scene.h"

static const char* const food[][4] = {
    {"Sardine", "Squid", "Mackerel", "Icefish"},
    {"Charred elk", "Roasted ram", "Wild boar", "Gold ore"},
    {"Hay", "Lettuce", "Carrot", "Banana slices"},
    {"Fresh greens", "Veggies", "Fish pellets", "Pizza"},
};

void draw_eat_scene(Canvas* canvas, uint32_t current_y, uint32_t pet_type) {
    canvas_clear(canvas);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_SARDINE_Y, AlignLeft, AlignTop, food[pet_type][0]);
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_SQUID_Y, AlignLeft, AlignTop, food[pet_type][1]);
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_MACKEREL_Y, AlignLeft, AlignTop, food[pet_type][2]);
    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X, FOOD_ICEFISH_Y, AlignLeft, AlignTop, food[pet_type][3]);

    canvas_set_color(canvas, ColorBlack);
    canvas_draw_box(canvas, 0, current_y - 2, 128, 12);

    canvas_invert_color(canvas);

    if(current_y == FOOD_SARDINE_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_SARDINE_Y, AlignLeft, AlignTop, food[pet_type][0]);
    else if(current_y == FOOD_SQUID_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_SQUID_Y, AlignLeft, AlignTop, food[pet_type][1]);
    else if(current_y == FOOD_MACKEREL_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_MACKEREL_Y, AlignLeft, AlignTop, food[pet_type][2]);
    else if(current_y == FOOD_ICEFISH_Y)
        elements_multiline_text_aligned(
            canvas, CHOICE_SCENE_X, FOOD_ICEFISH_Y, AlignLeft, AlignTop, food[pet_type][3]);

    elements_multiline_text_aligned(
        canvas, CHOICE_SCENE_X - 4, current_y, AlignRight, AlignTop, ">");
}
