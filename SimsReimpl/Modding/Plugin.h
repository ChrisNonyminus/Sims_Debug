#pragma once
#ifdef STANDALONE
#define MODDING_DISABLED
#endif
#ifndef MODDING_DISABLED

#include <vector.h>

#include "Hooks/Hooks.h"

// TODO
class cXObject;
struct StackElem;
struct BehaviorNode;
/* struct */ union XPrimParam;
class TSPlugin {
public:
  virtual ~TSPlugin() {}
  virtual void OnObjectEdithPrim(cXObject *obj, StackElem *elem,
                                 BehaviorNode *instruction) {}
  virtual void OnObjectGenericSimCall(cXObject *obj, StackElem *elem,
                                      XPrimParam *operand) {}
  virtual void OnObjectInitialize(cXObject *obj) {}
};
extern vector<TSPlugin *> gPlugins;

namespace Modding {
int __thiscall ObjectOnTryElementHook(cXObject *self, StackElem *elem,
                                      BehaviorNode *instr);
void InstallHooks();
void LoadPlugins();
} // namespace Modding

#endif
