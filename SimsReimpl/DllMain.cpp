#include <bstring.h>
#include <vector.h>

#include <windows.h>

#include "mapview.h"

// see
// https://github.com/OmniBlade/LasMarionetas/blob/b1f378c92dca777b31cc8dfe0cebe3f8f6c345c7/src/hookproxy/proxydll.cpp#L133

#pragma comment(linker, "/export:DirectSoundCreate=_FakeDirectSoundCreate,@1")

FARPROC OriginalDirectSoundCreate;
extern "C" __declspec(naked) void FakeDirectSoundCreate() {
  _asm {jmp[OriginalDirectSoundCreate]}
}

#pragma comment(linker,                                                        \
                "/export:DirectSoundEnumerateA=_FakeDirectSoundEnumerateA")

FARPROC OriginalDirectSoundEnumerateA;
extern "C" __declspec(naked) void FakeDirectSoundEnumerateA() {
  _asm {jmp[OriginalDirectSoundEnumerateA]}
}

namespace Reimpl {

FILE *log = NULL;
DWORD s_oldProtect1 = 0;
DWORD s_oldProtect2 = 0;
bool StartHooks() {
  bool success = false;
  ImageSectionInfo info;

  if (GetModuleSectionInfo(info)) {
    success = true;
    HANDLE process = GetCurrentProcess();
    if (VirtualProtectEx(process, info.BaseOfCode, info.SizeOfCode,
                         PAGE_EXECUTE_READWRITE, &s_oldProtect1) == FALSE) {
      fprintf(log, "VirtualProtect Failed; %u\n", GetLastError());
      success = false;
    }
    // TODO: this seems to fail because BaseOfData is 0x1000 for some reason.
    /* if (VirtualProtectEx(process, info.BaseOfData, info.SizeOfData,
                PAGE_EXECUTE_READWRITE, &s_oldProtect2) == FALSE) {
          fprintf(log, "VirtualProtect Failed; %u\n", GetLastError());
      success = false;
        } */
  }

  return success;
}
void SetupHooks();

bool StopHooks() {
  bool success = false;
  DWORD old_protect;
  ImageSectionInfo info;

  if (GetModuleSectionInfo(info)) {
    success = true;
    HANDLE process = GetCurrentProcess();
    if (VirtualProtectEx(process, info.BaseOfCode, info.SizeOfCode,
                         s_oldProtect1, &old_protect) == FALSE)
      success = false;
    /* if (VirtualProtectEx(process, info.BaseOfData, info.SizeOfData,
                         s_oldProtect2, &old_protect) == FALSE)
      success = false; */
  }

  return success;
}

void LoadForwardedFunctions() {
#define LIBNAME "\\dsound.dll"
  static const char dllName[] = LIBNAME;
  char path[MAX_PATH];
  memcpy(path + GetSystemDirectoryA(path, MAX_PATH - sizeof(dllName)), dllName,
         sizeof(dllName));
  HMODULE dll = LoadLibraryA(path);
  if (dll == NULL) {
    MessageBoxA(NULL, "Cannot load original dsound library.", "SimsReimpl",
                MB_ICONERROR);
    ExitProcess(0);
  } else {
    OriginalDirectSoundCreate = GetProcAddress(dll, "DirectSoundCreate");
    OriginalDirectSoundEnumerateA =
        GetProcAddress(dll, "DirectSoundEnumerateA");
  }
}
} // namespace Reimpl

// definitions/template-specs for STL stuff
vector<char>::vector_allocator vector<char>::static_allocator;
vector<string>::vector_allocator vector<string>::static_allocator;

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                    LPVOID lpReserved) {
  switch (ul_reason_for_call) {
  case DLL_PROCESS_ATTACH:
    Reimpl::log = fopen("log.txt", "w");
    Reimpl::LoadForwardedFunctions();
    if (Reimpl::StartHooks()) {
      Reimpl::SetupHooks();
      Reimpl::StopHooks();
    }

    break;

  case DLL_PROCESS_DETACH:
    // Currently does not unhook from module. Must shutdown.
    break;

  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  default:
    break;
  }

  return TRUE;
}
