

#include "main_p.h"
#include <stdbool.h>

/*
 * Often we would write main as:
 *
 * int main(void)
 * {
 *      mod_Init();
 *
 *      while(true) {
 *          mod_GetInt();
 *      }
 * }
 *
 * However, because the while loop will loop forever we cannot unit test this.
 * To work around this move the init and loop body to be 'private' functions
 * that can be unit tested. The main loop still can not be unit tested, but
 * we will minimize the amount of untestable code.
 */

int main(void)
{
    main_Init();

    while(true)
    {
        main_Loop();
    }
}
