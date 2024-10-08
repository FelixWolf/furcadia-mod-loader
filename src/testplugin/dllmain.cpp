#include "dllmain.h"
#include "pluginlib.h"
#include <windows.h>
#include <string>

PluginInfo_t *PluginInfo;

void buildPluginInfo()
{
    PluginInfo->pluginName = "Test Plugin";
    PluginInfo->pluginAuthor = "Felix";
}

PluginInfo_t* getPluginInfo()
{
    return PluginInfo;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch(ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            buildPluginInfo();
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
