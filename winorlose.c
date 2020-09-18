/** @file   winorlose.c
    @author A Josephs, C. Dewhurst
    @date   16 October 2019
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "winorlose.h"
#include "button.h"

/* Winner message
 * white button press restarts the game
 */
void winner(void)
{
    _Bool done = 0;
    tinygl_clear();
    tinygl_text_speed_set(10);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("YOU WON!! ");

    while(!done) {
        pacer_wait();
        tinygl_update();
        button_update();
        if (button_push_event_p (0)) {
            done = 1;
        }
    }
}

/* Loser message
 * white button press restarts the game
 */
void loser(void)
{
    _Bool done = 0;
    tinygl_clear();
    tinygl_update();
    tinygl_text_speed_set(10);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("YOU LOST >.< ");

    while(!done) {
        pacer_wait();
        button_update();
        tinygl_update();
        if (button_push_event_p (0)) {
            tinygl_clear();
            done = 1;
        }
    }
}

