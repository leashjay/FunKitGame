/** @file   gameplay.c
    @author A Josephs, C. Dewhurst
    @date   16 October 2019
*/

#include <stdlib.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "gameplay.h"
#include "displaycharacter.h"

#define game_speed 750
#define speed_up_factor 50



static char game_state = 'U';
static int rounds_compl = 0;

/*
 * Function to retrieve game state
 * of play
 * U: Holding state
 * N: Non-Active Player
 * A: Active Player
 */
char get_game_state(void)
{
    return game_state;
}


/*
 *Function call to change the state
 * of the game, takes param: char
 */
void set_game_state(char value)
{
    game_state = value;
}


/* Function that gives pseudo random instruction
 * if time, change this to have a random seed
 * U: UP
 * D: Down
 * R: Right
 * L: Left
 */
char give_direction(void)
{
    char c = '!';
    int n;

    n = (rand () % 5);

    if(n == 1) {
        c = 'U';
    } else if(n == 2) {
        c = 'D';
    } else if(n == 3) {
        c = 'L';
    } else if(n == 4) {
        c = 'R';
    } else if(n == 0) {
        c = 'P';
    }
    return c;
}


/*
 * Assigns character to variable input_event dependant
 * on nav switch action for logic tests
 */
char get_input_event_as_char(char input_event)
{
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        input_event = 'R';
    } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        input_event = 'L';
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        input_event = 'U';
    } else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        input_event = 'D';
    } else if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        input_event = 'P';
    }
    return input_event;
}


/*
 * Compares input action with instruction direction flashed
 * Returns 1: input matched display,
 *         2: input did not match
 *         0: no action input by player
 */
int action_comparison(char input_event, char direction)
{
    uint16_t result = 0;

    if(input_event == direction) {
        result = 1;
    } else if(input_event == '!') {
        result = 0;
    } else if(input_event != direction) {
        result = 2;
    }
    return result;
}


/*
 * Function to compare action with instruction
 * If the actions are the same
 * Returns 1: input matched display,
 *         2: input did not match
 *         0: no action input by player
 */
char button_pressed(char direction)
{
    char input_event = '!';
    uint16_t result = 0;

    input_event = get_input_event_as_char(input_event);
    result = action_comparison(input_event, direction);

    return result;
}


/* Main game function */
void run_game(void)
{
    /* Declare variables */
    char direction = '*';
    uint16_t rounds = 0;
    uint16_t counter = 1;
    uint16_t first = 1;
    uint16_t success = 0;
    _Bool in_play = 1;

    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text_speed_set(5);

    while(in_play) {
        pacer_wait();
        navswitch_update();
        tinygl_update();
        // ir_uart_putc((char) counter);

        /* Loop runs every 1.5 secs.
         * 500 too quick, 1000 too slow
         * Decreasing variable for increased game speed.
         * calculated based on rounds undertaken and increases
         * speed by factor of ~50
         */
        if (counter % (game_speed - (rounds_compl * speed_up_factor)) == 0) {

            /* Gives instruction if no instruction has been given previously or if previous action was successful */
            if(first == 1 || success == 1) {

                /* Breaks loop if player succeeds 5 times */
                if(rounds == 5) {

                    rounds = 0;
                    first = 1;
                    success = 0;
                    counter = 1;
                    rounds_compl++;

                    tinygl_clear();
                    ir_uart_putc('A');
                    set_game_state('N');
                    in_play = 0;

                } else {
                    tinygl_clear();
                    first = 0;
                    success = 0;
                    direction = give_direction();
                    display_character(direction);
                    rounds++;
                }
            }

            /* If unsuccessful, send players to win/loss screens */
            else {
                ir_uart_putc('W');
                rounds_compl = 0;
                set_game_state('L');
                in_play = 0;
            }

            counter = 0;
        }

        in_play = 1;

        /* Checks that an instruction has been given and that no action has been taken */
        if(first != 1 && success == 0) {

            success = button_pressed(direction);
        }

        counter++;

        /* Fail safe to break loop if gamestate changes */
        if(get_game_state() != 'A') {
            break;
        }
    }
}
