#include "npea00387.h"

// binds
#define BTN_ACTION (BTN_L2 | BTN_R2)
#define BTN_ALT BTN_R1

#define BTN_RELOAD BTN_CRO
#define BTN_SAVE BTN_SQU
#define BTN_LOAD BTN_CIR

// variables
#define i (*((int*)0xD9FEFC))
#define save_pos ((void*)0xD9FF00)
#define save_save ((void*)0x1100000)

// macros
#define down(button) ((down_buttons & (button)) == (button))
#define pressed(button) ((pressed_buttons & (button)) == (button))


void entry() {
    // L2 + R2
    if (!down(BTN_ACTION)) {
        return;
    }

    // R1
    if (down(BTN_ALT)) {
        // SQUARE or CIRCLE and not saved
        if (pressed(BTN_SAVE) || (pressed(BTN_LOAD) && *(int*)save_save == 0)) {
            // prevent stack overflow from giga memcpy
            for (i = 0; i < 0x200000; i += 0x8000) {
                memcpy((void*)((int)save_save + i), (void*)((int)savedata_buf + i), 0x8000);
            }
        }

        // SQUARE or CIRCLE
        if (pressed(BTN_SAVE) || pressed(BTN_LOAD)) {
            perform_load(0, save_save);
        }

        goto clear;
    }

    // CROSS
    if (pressed(BTN_RELOAD)) {
        destination_planet = current_planet;
        should_load = 1;

        goto clear;
    }

    // SQUARE
    if (pressed(BTN_SAVE)) {
        memcpy(save_pos, &player_pos, 0x20);

        goto clear;
    }

    // CIRCLE
    if (pressed(BTN_LOAD)) {
        memcpy(&player_pos, save_pos, 0x20);

        goto clear;
    }

clear:
    down_buttons = BTN_ACTION | (BTN_ALT & down_buttons);
    pressed_buttons = 0;
    released_buttons = 0;
}