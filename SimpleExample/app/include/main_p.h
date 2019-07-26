#ifndef __MAIN_P_H__
#define __MAIN_P_H__

#include "main.h"

// These are "private" to main and are here so we can maximize the amount of code
// that has unit tests. Some times there might be more that one "init" function
// to support instances where one part of the system needs to be initialized
// before another.

void main_Init(void);
void main_Loop(void);

#endif
