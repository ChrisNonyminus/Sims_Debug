#include <bstring.h>

class cRZString : public string {
  int xC;

public:
  cRZString();
  virtual sub_40F178(); // vtable+0 (virtual destructor)
  virtual sub_888D60(); // vtable+4
  virtual sub_888DF0(); // vtable+8
  virtual sub_888E80(); // vtable+C
};

// FUNCTION: 0x00488040
cRZString::cRZString() { xC = 0; }
