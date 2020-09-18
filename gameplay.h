#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/* Function the returns gamestate */
char get_game_state(void);

/*
 *Function call to change the state
 * of the game, takes param: char
 */
void set_game_state(char value);

/*
 *Function call to change the state
 * of the game, takes param: char
 */
void set_game_state(char value);

/* Function that gives pseudo random instruction
 * if time, change this to have a random seed
 * U: UP
 * D: Down
 * R: Right
 * L: Left
 */
char give_direction(void);

/* Assigns character to variable input_event dependant
 * on nav switch action for logic tests
 */
char get_input_event_as_char(char input_event);

/* Compares input action with instruction direction flashed
 * Returns 1: input matched display,
 *         2: input did not match
 *         0: no action input by player
 */
int action_comparison(char input_event, char direction);

/* Function to compare action with instruction
 * If the actions are the same
 * Returns 1: input matched display,
 *         2: input did not match
 *         0: no action input by player
 */
char button_pressed(char direction);

/* Main game function */
void run_game(void);

#endif
