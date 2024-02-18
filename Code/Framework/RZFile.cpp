#include "Framework/RZFile.h"

unsigned int cRZFile::SeekToEnd() { return Seek(0, 2); }
