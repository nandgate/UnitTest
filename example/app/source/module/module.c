#include "module/module_p.h"

int mod_localState;

void mod_Init(void)
{
    mod_localState = MOD_DEFAULT_STATE;
}
