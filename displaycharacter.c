#include "tinygl.h"
#include "displaycharacter.h"

/*
 * Function to display character
 */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}
