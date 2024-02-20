#include "msrc/Util/SRand.h"
int seed = 0x6403C445;

unsigned int GetNextRandomNumber(void) {
  unsigned int seedLo, seedHi;
  unsigned int seedLoMulL, seedLoMulH;
  unsigned int seedHiMulH, seedHiMulL;
  const unsigned int magic = 1103515245;

  seedLo = seed & 0xffff;
  seedHi = seed >> 16;
  seed = seed * magic + 12345;
  seedLoMulL = seedLo * (magic & 0xffff);
  seedLoMulH = seedLo * (magic >> 16);
  seedHiMulL = seedHi * (magic & 0xffff);
  seedHiMulH = seedHi * (magic >> 16);
  return (((seedLoMulL + 12345) >> 16) + seedLoMulH) + seedHiMulL +
         (seedHiMulH << 16);
}

int GetSRandSeed(void) { return seed; }

void SetSRandSeed(int s) { seed = s; }

#ifndef STANDALONE
void InstallSRandHooks() {
#ifdef COMPLETE_COLLECTION
#else // assume Sims_Debug.exe build
  Hook_Function(0x00508C50, GetSRandSeed);
  Hook_Function(0x00508C70, SetSRandSeed);
  Hook_Function(0x00508E80, GetNextRandomNumber);
  // Hook_Memory
#endif
}
#endif
