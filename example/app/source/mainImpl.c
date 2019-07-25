#include "main_p.h"
#include "module/module.h"

inline void main_Init(void)
{
    mod_Init();
}

inline void main_Loop(void)
{
    mod_GetInt();
}
