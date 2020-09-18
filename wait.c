/** @file   wait.c
    @author A Josephs, C. Dewhurst
    @date   16 October 2019
*/


#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "wait.h"
#include "displaycharacter.h"
#include "gameplay.h"

/* Non-active player wait screen */
void nonactive_player(void)
{
    char ch = '*';

    tinygl_clear();
    display_character('*');
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);

    while(1) {

        pacer_wait();
        tinygl_update();

        if(ir_uart_read_ready_p ()) {

            ch = ir_uart_getc();

            if(ch == 'W') {
                set_game_state('W');
                break;
            }
            if(ch == 'A'){
                set_game_state('A');
                break;
            }
        }
        if(get_game_state() != 'N'){

            break;
        }
    }
}
