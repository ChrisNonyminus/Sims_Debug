#include <WINDOWS.H>

#include <CRTDBG.H>

class cRZCmdLine;

namespace Gonzo {
    unsigned Main(cRZCmdLine *pCmdLine);
};

extern unsigned dword_FFD9A0;

void gzframe_0087193c(cRZCmdLine *pCmdLine);
void sub_828160(int a);

unsigned Gonzo::Main(cRZCmdLine *pCmdLine) {
    char pad[0x40];
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
    int v = 0;
    if (v) {
        sub_828160(v);
    }
    gzframe_0087193c(pCmdLine);

    return dword_FFD9A0;
}
