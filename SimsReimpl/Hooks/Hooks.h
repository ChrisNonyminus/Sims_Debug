// This code is from Thyme. See
// https://github.com/TheAssemblyArmada/Thyme/blob/develop/src/hooker/hooker.h
/*
 * @copyright Thyme is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 *
 */

#pragma once

#include <WINDOWS.H>

// Helper Functions based on those from OpenMC2

// Use Make_Global to access global variables in the original exe once you know
// the correct type and address. This should not change from run to run if the
// exe loads at a standard base address.

// Typical use will be to use define to create a friendly name, e.g:
// #define SomeGlobalVar (Make_Global<bool>(0x00FF00FF))
// allows you to use SomeGlobalVar as though it was a bool you declared, though
// it will reflect the value the original exe sees at address 0x00FF00FF
template <typename T> inline T &Make_Global(const unsigned int address) {
  return *reinterpret_cast<T *>(address);
}

template <typename T> inline T *Make_Pointer(const unsigned int address) {
  return reinterpret_cast<T *>(address);
}

// C++98 does not support variadic arguments, so I have to try something else
// than this :(
/*
// Call_Function and Call_Method can be used to call functions from the original
// binary where they are required and a replacement hasn't been written yet.
template <typename ReturnType, typename... Arguments>
inline ReturnType Call_Function(const unsigned int address, Arguments... args) {
  return reinterpret_cast<ReturnType(__cdecl *)(Arguments...)>(address)(
      args...);
}

template <typename ReturnType, typename... Arguments>
inline ReturnType Call__StdCall_Function(const unsigned int address,
                                         Arguments... args) {
  return reinterpret_cast<ReturnType(__stdcall *)(Arguments...)>(address)(
      args...);
}

template <typename ReturnType, typename ThisType, typename... Arguments>
inline ReturnType Call_Method(const unsigned int address, ThisType *const self,
                              Arguments... args) {
  return reinterpret_cast<ReturnType(__thiscall *)(ThisType *, Arguments...)>(
      address)(self, args...);
}

// These create pointers to various types of function where the return,
// parameters and calling convention are known.
template <typename ReturnType, typename... Arguments>
inline ReturnType(__cdecl *Make_Function_Ptr(const unsigned int address))(
    Arguments...) {
  return reinterpret_cast<ReturnType(__cdecl *)(Arguments...)>(address);
}

template <typename ReturnType, typename... Arguments>
inline ReturnType(__stdcall *Make_StdCall_Ptr(const unsigned int address))(
    Arguments...) {
  return reinterpret_cast<ReturnType(__stdcall *)(Arguments...)>(address);
}

template <typename ReturnType, typename ThisType, typename... Arguments>
inline ReturnType(__thiscall *Make_Method_Ptr(const unsigned int address))(
    ThisType *, Arguments...) {
  return reinterpret_cast<ReturnType(__thiscall *)(ThisType *, Arguments...)>(
      address);
}

template <typename ReturnType, typename... Arguments>
inline ReturnType(__cdecl *Make_VA_Function_Ptr(const unsigned int address))(
    Arguments..., ...) {
  return reinterpret_cast<ReturnType(__cdecl *)(Arguments..., ...)>(address);
} */

#define MAKE_FUNCTION_PTR(name, address, returntype, args)                     \
  typedef returntype(__cdecl *name##Func) args;                                \
  name##Func name##Ptr = (name##Func)((void *)address);

#define MAKE_STDCALL_PTR(name, address, returntype, stdargs)                   \
  typedef returntype(__stdcall *name##StdCallFunc) stdargs;                    \
  name##StdCallFunc name##StdCallPtr = (name##StdCallFunc)((void *)address);

#define MAKE_METHOD_PTR(clasname, name, address, returntype, methodargs)       \
  typedef returntype(__thiscall *classname##name##MethodFunc) methodargs;      \
  classname##name##MethodFunc clasname::name##MethodPtr =                      \
      (classname##name##MethodFunc)((void *)address);

#define DECLARE_FUNCTION_PTR(name, returntype, args)                           \
  extern returntype(__cdecl *name##Ptr) args;

#define DECLARE_STDCALL_PTR(name, returntype, stdargs)                         \
  extern returntype(__stdcall *name##StdCallPtr) stdargs;

#define DECLARE_METHOD_PTR(name, returntype, methodargs)                       \
  static returntype(__thiscall *name##MethodPtr) methodargs;

#define FUNCTION_PTR_VAR(name) name##Ptr
#define STDCALL_PTR_VAR(name) name##StdCallPtr
#define METHOD_PTR_VAR(name) name##MethodPtr

// A nice struct to pack the assembly in for jumping into replacement code.
// So long as the calling conventions and arguments for the replaced and
// replacement functions are the same, everything should just work.
#pragma pack(push, 1)
struct x86_jump {
  unsigned char cmd;
  unsigned int addr;
};
#pragma pack(pop)

// Use these to hook existing functions and replace them with newly written ones
// to either replace them permanently or just to test correctness of a newly
// written one.

// Base hooking function to apply the actual hook.
inline void Hook_Func(unsigned int in, unsigned int out) {
  /* static_assert(sizeof(x86_jump) == 5, "Jump struct not expected size."); */

  x86_jump cmd;
  cmd.cmd = 0xE9;
  cmd.addr = out - in - 5;
  WriteProcessMemory(GetCurrentProcess(), (LPVOID)in, &cmd, 5, NULL);
}

template <typename T> void Hook_Memory(unsigned int in, T out) {
  WriteProcessMemory(GetCurrentProcess(), (LPVOID)in, &out, sizeof(T), NULL);
}

// Hook regular functions and static methods.
template <typename T> void Hook_Function(unsigned int in, T out) {
  Hook_Func(in, reinterpret_cast<unsigned int>(out));
}

// Method pointers need funky syntax to get the underlying function address
// hence the odd cast to void for the out pointer.
template <typename T> void Hook_Method(unsigned int in, T out) {
  Hook_Func(in, reinterpret_cast<unsigned int>((void *&)out));
}

// Virtuals are even trickier so resort to inline assembler for those courtesy
// of the TTScripts guys.
#define Hook_Any(in, out)                                                      \
  __asm { \
      __asm push out                  \
      __asm push in                         \
      __asm call Hook_Func     \
      __asm add esp, 8 }
