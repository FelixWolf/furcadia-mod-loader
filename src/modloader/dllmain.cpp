#include "wsock32_impl.hpp"
#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <chrono>
#include "sha256.h"

typedef void (*FurcMessageFunc)(char*);

void init()
{
    /*
    void* targetAddress = (void*)0x00414270;
    size_t hookSize = 6;
    originalHandleProtocolMessage = (HandleProtocolMessage_t)HookFunction(targetAddress, (void*)MyHandleProtocolMessage, hookSize);

    uintptr_t funAddress = 0x00411f00;
    FurcMessageFunc furcMessage = reinterpret_cast<FurcMessageFunc>(funAddress);
    */
    printf("Mod loader injected!");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            if(!setupWSock32Forwarding())
            {
                MessageBoxA(NULL, "Could not locate native wsock32.dll!"
"\nIf this persists, delete the wsock32.dll from your Furcadia install directory."
"\n\nFurcadia will now close.",
                    "Furcadia Mod Loader",
                    MB_OK | MB_ICONERROR
                );
                ExitProcess(1);
            }
            init();
            break;
        
        case DLL_PROCESS_DETACH:
            freeWSock32();
            break;
        
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
