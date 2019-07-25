#include "module/module_p.h"

int mod_GetInt(void)
{
    return mod_Compute() + MOD_THE_INT;
}