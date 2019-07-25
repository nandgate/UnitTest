#ifndef __MODULE_P_H__
#define __MODULE_P_H__

// These are things that are known only to the module and 'private' to the
// reset of the app. The private header should NEVER be included outside of the
// module. The private header should also be included by the unit tests.

#include "module.h"     // Private header includes the public header

#define MOD_DEFAULT_STATE   1234

#define MOD_THE_INT 42

int mod_Compute(void);

#endif
