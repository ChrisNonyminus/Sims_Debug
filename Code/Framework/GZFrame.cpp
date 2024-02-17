#include <WINDOWS.H>

#include <CRTDBG.H>

#include "Hooks/Hooks.h"

#include "Framework/GZFrame.h"

#define dword_FFD9A0 Make_Global<unsigned>(0x00FFD9A0)

MAKE_FUNCTION_PTR(cGZFramework__CreateAndRun, 0x00871830, void,
                  (cRZCmdLine * pCmdLine))

MAKE_FUNCTION_PTR(sub_828160, 0x828160, void, (int))
/*
// FUNCTION: 0x00871830
void cGZFramework__CreateAndRun(cRZCmdLine *pCmdLine);
void sub_828160(int a); */

#define cGZFramework__CreateAndRun cGZFramework__CreateAndRunPtr
#define sub_828160 sub_828160Ptr

unsigned Gonzo::Main(cRZCmdLine *pCmdLine) {

  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
  int v = 0;
  if (v) {
    sub_828160(v);
  }
  cGZFramework__CreateAndRun(pCmdLine);

  return dword_FFD9A0;
}
