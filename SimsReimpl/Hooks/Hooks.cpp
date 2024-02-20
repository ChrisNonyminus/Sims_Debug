#include "Hooks.h"

#include <new>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <crtdbg.h>

#include "Framework/GZFrame.h"

#include "Framework/RZFile.h"

#include "Sims/SimsApp.h"

#include "msrc/Util/SRand.h"

#include "Modding/Plugin.h"

void *crt_new(size_t n) { return ::operator new(n); }

void crt_del(void *p) { ::operator delete(p); }

void *crt_placement_new(size_t n, void *p) { return ::operator new(n, p); }

void crt_placement_del(void *p, void *p1) { ::operator delete(p, p1); }

namespace Reimpl {
/*
void __thiscall TestOpenMemViewOverride(cSimsApp *app) {
  cSimsApp::METHOD_PTR_VAR(ShowSimpleMessageBox)(
      app, "Kilroy was here", "cSimsApp::OpenMemView OVERRIDDEN", 0, 0);
} */

void InstallHookTests() {
  /*Hook_Function(0x00652E90, //cSimsApp::OpenMemView
                TestOpenMemViewOverride);*/
}

void SetupFrameworkHooks() {
  Hook_Function(0x00871C80, Gonzo::Main);
  Hook_Method(0x008F76A0, &cRZFile::SeekToEnd);
}

// when hooking, we have to make sure the CRT functions that control state (i.e
// allocation functions) are handled by the DLL (us)

void SetupMSVCRTHooks() {
  /* Hook_Function(0x00A04009, free);
  Hook_Function(0x00826F80, malloc);
  Hook_Function(0x00827B50, _free_dbg);
  Hook_Function(0x00826FB0, _malloc_dbg);
  Hook_Function(0x008274A0, _realloc_dbg);
  Hook_Function(0x008273E0, calloc);
  Hook_Function(0x00827470, realloc);
  Hook_Function(0x0082D260, fseek);
  Hook_Function(0x0082D090, fread);
  Hook_Function(0x00829A60, fopen);
  Hook_Function(0x00829440, fclose);
  Hook_Function(0x0040A079, crt_placement_new);
  Hook_Function(0x00406B59, crt_placement_del);
  Hook_Function(0x0082FD00, strdup);
  Hook_Function(0x008293D0, atexit); */
}
void SetupHooks() {
#ifndef MODDING_DISABLED
  Modding::LoadPlugins();
#endif

  SetupMSVCRTHooks();
  SetupFrameworkHooks();

  // msrc
  InstallSRandHooks();

#ifndef NO_FUNNY_BUSINESS
  InstallHookTests();
#endif
#ifndef MODDING_DISABLED
  Modding::InstallHooks();
#endif
}
} // namespace Reimpl