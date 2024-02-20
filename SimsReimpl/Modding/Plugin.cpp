#ifndef MODDING_DISABLED
#include "Plugin.h"

#include "msrc/Behavior/Object.h"

#include "Sims/SimsApp.h"

vector<TSPlugin *> gPlugins;
vector<TSPlugin *>::vector_allocator vector<TSPlugin *>::static_allocator;

namespace Modding {
int __thiscall ObjectOnTryElementHook(cXObject *self, StackElem *elem,
                                      BehaviorNode *instr) {
  int ret = cXObject::OnTryElementMethodPtr(self, elem, instr);
  for (int i = 0; i < gPlugins.size(); i++) {
    if (gPlugins[i]) {
      gPlugins[i]->OnObjectEdithPrim(self, elem, instr);
    }
  }
  return ret;
}
void InstallHooks() {
  Hook_Function(cXObject::kThunk_OnTryElement, ObjectOnTryElementHook);
}

class TSPluginTest : public TSPlugin {
public:
  void OnObjectEdithPrim(cXObject *obj, StackElem *elem, BehaviorNode *instr) {
    /* if (instr->opcode == kPrim_Tutorial) {
      cSimsApp::ShowSimpleMessageBoxMethodPtr(gpApp, "Kilroy was here",
                                              "Tutorial event hook test", 0, 0);
    } */
  }
};

TSPluginTest t;
// TODO: load from DLLs
void LoadPlugins() { gPlugins.push_back(&t); }
} // namespace Modding

#endif