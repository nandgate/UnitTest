#include "main_p.h"
#include "module/module.h"

// The real work of the main function is here. Also, as the implementations
// become more sophisticated each function is likely to be moved to it own
// file.

void main_Init(void)
{
    mod_Init();
}

void main_Loop(void)
{
    mod_GetInt();
}
