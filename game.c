/** @file   gameplay.c
    @author A Josephs, C. Dewhurst
    @date   16 October 2019
 *
 * Game starts when player pressed black navigation key
 * A direction will flash on the the screen
 * The player must respond before the character dissapears
 * After 5 correct reactions the game play is passed over to Player 2
 * If a player misses a reaction they instantly lose
 * The game may be restarted by pressing the white button
 */

#include "winorlose.h"
#include "initialise.h"
#include "displaycharacter.h"
#include "gameplay.h"
#include "wait.h"
#include "ir_uart.h"

/*
 *Main game function call
 *checks gamestate and sends
 * player to appropriate screen
 */
void new_game(void)
{
    _Bool game = 0;

    initialise_controller();
    start_game();

    while (!game) {
        if(get_game_state() == 'A') {
            run_game();
        } else if (get_game_state() == 'N') {
            nonactive_player();
        } else if (get_game_state() == 'L') {
            loser();
            game = 1;
        } else if (get_game_state() == 'W') {
            winner();
            game = 1;
        }
    }
}


/* Main function calls game start
 * game loops and restarts when reset button
 * pressed
 */
int main (void)
{
    while(1) {
        new_game();
    }
    return 0;
}
