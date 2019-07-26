#include "module/module_p.h"

// The "init" function always goes in a file that has the same name as the
// module. All modules have init functions, even if they are empty.

// State local to the module is declared in a file that has the same name as
// the module. Source files in the module that use the value will extern them.
// The extern for the local variable is never pull-in via a header file.

int mod_localState;

void mod_Init(void)
{
    mod_localState = MOD_DEFAULT_STATE;
}
