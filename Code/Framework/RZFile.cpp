#include "Framework/RZFile.h"
#include "RZFile.h"

unsigned int cRZFile::SeekToEnd() { return Seek(0, 2); }
