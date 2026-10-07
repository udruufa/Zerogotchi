#include "feedback.h"
#include <furi_hal.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>

static const NotificationSequence win_sound = {
    &message_note_a5,
    &message_delay_100,
    &message_note_cs6,
    &message_delay_100,
    &message_note_e6,
    &message_note_fs6,
    &message_delay_100,
    &message_note_a6,
    &message_delay_100,
    &message_note_e6,
    &message_delay_100,
    &message_note_cs6,
    &message_delay_100,
    &message_note_a5,
    &message_delay_100,
    &message_sound_off,
    NULL,
};
static const NotificationSequence loss_sound = {
    &message_note_c4,
    &message_delay_100,
    &message_note_b4,
    &message_delay_100,
    &message_note_b4,
    &message_delay_100,
    &message_note_as4,
    &message_delay_100,
    &message_note_a4,
    &message_delay_100,
    &message_note_gs4,
    &message_delay_100,
    &message_note_fs4,
    &message_delay_100,
    &message_note_c4,
    &message_delay_100,
    &message_sound_off,
    NULL,
};
static const NotificationSequence end_sound = {
    &message_note_a4,
    &message_delay_100,
    &message_note_a4,
    &message_delay_100,
    &message_note_a4,
    &message_delay_100,
    &message_note_a4,
    &message_delay_100,
    &message_note_c5,
    &message_delay_100,
    &message_note_b4,
    &message_delay_100,
    &message_note_as4,
    &message_delay_100,
    &message_note_a4,
    &message_delay_100,
    &message_sound_off,
    NULL,
};

void feedback_vibration(AppContext* app) {
    furi_hal_vibro_on(true);
    furi_delay_ms(250);
    furi_hal_vibro_on(false);
    furi_delay_ms(250);
    furi_hal_vibro_on(true);
    furi_delay_ms(250);
    furi_hal_vibro_on(false);
    furi_delay_ms(250);
    furi_hal_vibro_on(true);
    furi_delay_ms(250);
    furi_hal_vibro_on(false);
    furi_delay_ms(250);
    furi_hal_vibro_on(true);
    furi_delay_ms(250);
    furi_hal_vibro_on(false);
    UNUSED(app);
}

void feedback_sound(AppContext* app) {
    NotificationApp* notifications = furi_record_open(RECORD_NOTIFICATION);

    switch(app->sound) {
    case(WIN):
        notification_message(notifications, &win_sound);
        break;
    case(LOSS):
        notification_message(notifications, &loss_sound);
        break;
    case(END):
        notification_message(notifications, &end_sound);
        break;
    default:
        break;
    }

    furi_record_close(RECORD_NOTIFICATION);
}
