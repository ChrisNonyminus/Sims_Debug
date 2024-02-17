#pragma once

#include "Framework/IGZFile.h"

class cRZFile : public cIGZFile {
public:
  unsigned int SeekToEnd();
};
