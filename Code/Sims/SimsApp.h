#pragma once

#ifndef STANDALONE
#include "Hooks/Hooks.h"
#endif

class cSimsApp {
#ifndef STANDALONE
public:
#define gpApp Make_Global<cSimsApp *>(0x00FEE3E0)
  DECLARE_METHOD_PTR(ShowSimpleMessageBox, int,
                     (cSimsApp * self, const char *szMessage,
                      const char *szTitle, int unk1, int unk2));
#endif
};
