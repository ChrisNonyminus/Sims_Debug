#pragma once
#ifndef STANDALONE
#include "Hooks/Hooks.h"
#endif

struct StackElem {
  // TODO
  unsigned char byte_0[4];
  unsigned short word_4;
  unsigned char byte_6[1];
  char byte_7;
  unsigned int dword_8;
  unsigned int dword_c;
  unsigned int dword_10;
};
union XPrimParam {
  unsigned char operands[8];
};
struct BehaviorNode {
  unsigned short opcode;
  unsigned char tDest, fDest;
  XPrimParam param;
};
enum BehaviorPrim {
  kPrim_Idle,
  kPrim_GenericSimCall,
  kPrim_Expr,
  kPrim_Grab,
  kPrim_Drop,
  kPrim_Update,
  kPrim_Random,
  kPrim_Burn,
  kPrim_Tutorial,
  kPrim_DistanceTo,
  kPrim_ShowDialog = 36,
  kPrim_SetBalloon = 41,
  kPrim_MakeNewObject = 42,
};
class cXObject {
public:
  enum { kThunk_OnTryElement = 0x00411F2C };

  DECLARE_METHOD_PTR(OnTryElement, int,
                     (cXObject * self, StackElem *elem, BehaviorNode *instr));
};
