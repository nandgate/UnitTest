#ifndef __MODULE_H__
#define __MODULE_H__

// These are things that are known to the module and 'public' to the reset of
// the app. The public header should be included outside of the module.

#define MOD_SOME_CONST 42

void mod_Init(void);
int mod_GetInt(void);

#endif
