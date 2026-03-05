
#include <windows.h> 


BOOL APIENTRY DllMain(HINSTANCE h, DWORD r, void*){
    if (r == 1){
        return MessageBoxA(NULL, "Injected!", "DLL INJECTION", 0);
    }
    return true;
}