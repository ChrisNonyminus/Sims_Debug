#include "Hooks.h"

#include <new>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <CRTDBG.H>

void *crt_new(size_t n) { return ::operator new(n); }

void crt_del(void *p) { ::operator delete(p); }

namespace Reimpl {

// when hooking, we have to make sure the CRT functions that control state (i.e
// allocation functions) are handled by the DLL (us)

void SetupMSVCRTHooks() {
  Hook_Function(0x00A04009, free);
  Hook_Function(0x00826F80, malloc);
  Hook_Function(0x00827B50, _free_dbg);
  Hook_Function(0x00826FB0, _malloc_dbg);
  Hook_Function(0x008273E0, calloc);
  Hook_Function(0x00827470, realloc);
  Hook_Function(0x0082D260, fseek);
  Hook_Function(0x0082D090, fread);
  Hook_Function(0x00829A60, fopen);
  Hook_Function(0x00829440, fclose);
  /* Hook_Function(0x0040D04E, crt_new);
  Hook_Function(, crt_del); */
  Hook_Function(0x0082FD00, strdup);
}
void SetupHooks() { SetupMSVCRTHooks(); }
} // namespace Reimpl