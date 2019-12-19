#include "npea00387.h"

// binds
#define BTN_ACTION (BTN_L2 | BTN_R2)
#define BTN_ALT BTN_L3

#define BTN_RELOAD BTN_R3
#define BTN_SAVE BTN_L1
#define BTN_LOAD BTN_R1

// variables
#define i (*((int*)0xD9FEFC))
#define save_pos ((void*)0xD9FF00)
#define save_save ((void*)0x1100000)

// macros
#define down(button) ((down_buttons & (button)) == (button))
#define pressed(button) ((pressed_buttons & (button)) == (button))


void entry() {
    if (!down(BTN_ACTION)) {
        return;
    }

    // reload planet
    if (pressed(BTN_RELOAD)) {
        // reload save
        if (down(BTN_ALT)) {
            if (down(BTN_UP) || *(int*)save_save == 0) {
                // prevent stack overflow from giga memcpy
                for (i = 0; i < 0x200000; i += 0x8000) {
                    memcpy((void*)((int)save_save + i), (void*)((int)savedata_buf + i), 0x8000);
                }
            }

            perform_load(0, save_save);
        }
        // just reload planet
        else {
            destination_planet = current_planet;
            should_load = 1;
        }
    }
    // save pos
    else if (pressed(BTN_SAVE)) {
        memcpy(save_pos, &player_pos, 0x20);
    }
    // load pos
    else if (pressed(BTN_LOAD)) {
        memcpy(&player_pos, save_pos, 0x20);
    }
}