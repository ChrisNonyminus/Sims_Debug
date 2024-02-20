#ifndef STANDALONE
#include "Hooks/Hooks.h"
#endif

unsigned int GetNextRandomNumber(void);
int GetSRandSeed(void);
void SetSRandSeed(int);

#ifndef STANDALONE
void InstallSRandHooks();
#endif
