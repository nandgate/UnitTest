#ifndef __MODULE_H__
#define __MODULE_H__

// These are things that are known to the module and 'public' to the reset of
// the app. The public header should be included outside of the module.

// All of the names that are in the "module" are prefixed with "mod_" to create
// a "namesapce" for the module. Its best to keep the prefix short but
// descriptive. If I had an stepper motor module "sm_" is probably not
// descriptive enough, but "steppermotor_" is too long. I'd probably go with
// something like "step_".

// Again, declarations in this file are public and are therefore interface in
// nature. Implementation details should be minimal. Note that in C it is valid
// to declare the exsistance of a type without specifying its members. E.g.:
// In module.h can have: "typedef struct mod_foo_t;" and module_p,h can have
// the details: "typedef struct mod_foo_t { int x; };".

#define MOD_SOME_CONST 42

void mod_Init(void);
int mod_GetInt(void);

#endif
