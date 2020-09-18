#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"
#include "initialise.h"
#include "gameplay.h"
#include "button.h"

#define PACER_RATE 500
#define MESSAGE_RATE 25
#define LOOP_RATE 500

/* Initialise all devices used on controller  */
void initialise_controller(void)
{
    system_init ();
    pacer_init (PACER_RATE);
    tinygl_init (LOOP_RATE);
    navswitch_init ();
    ir_uart_init();
    button_init ();

}

/* Starting game message */
void start_game(void)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    tinygl_text ("TO START PRESS BLACK BUTTON... ");
    tinygl_update ();
    pacer_init (LOOP_RATE);

    while(1) {

        pacer_wait();
        navswitch_update();
        tinygl_update();

        /* Starts game for first player to push nav btton */
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {

            tinygl_clear();
            ir_uart_putc('N');
            set_game_state('A');
            break;
        }
        /* Player who does not press nav button gets sent to wait screen */
        if(ir_uart_read_ready_p()) {

            if(ir_uart_getc() == 'N') {

                set_game_state('N');
                break;
            }
        }
    }
}
