#ifndef PLUGINLIB_H
#define PLUGINLIB_H
#include <string>

// structVersion is two numbers:
// [0] must match the expected version as it changes something drastically, it
//  should reset [1]'s counter.
// [1] must only be incremented if it is a minor change that won't break
//  compatibility such as an addition.

// Response from plugin to getPluginInfo(); Must work independently from pluginInit();
struct PluginInfo_t {
    // Initialization
    unsigned int structVersion[2] = { 0, 0 };
    unsigned char expectedFurcadiaHash[32] = { 0 };
    bool requireHashMatch = false;
    
    // Plugin info
    int pluginVersion[4] = { 1, 0, 0, 0 };
    char pluginUUID[16] = { 0 };
    std::string pluginName = { 0 };
    std::string pluginAuthor = { 0 };
};

// Handles used in hooking
struct PluginHook_t {
    bool success; // If hook was successful
    bool hooked; // If still hooked
    char *target; // Hook name
    void *hook; // Hook pointer
};

// Passed from ModLoader to Plugin via pluginInit();
struct PluginAPI_t {
    // Initialization
    unsigned int structVersion[2] = { 0, 0 };
    unsigned char furcadiaHash[32] = { 0 };
    int modLoaderVersion[4] = { 1, 0, 0, 0 };
    
    // APIs
    void (*log)(int level, char*); // Log to the logger
    void (*error)(char*); // Actually create an error with the plugin
    void (*requestUnload)();
    void (*getFunction)(void*);
    PluginHook_t* (*addHook)(char*, void*);
    bool (*removeHook)(PluginHook_t*);
};

__declspec(dllexport) PluginInfo_t* getPluginInfo();
__declspec(dllexport) bool pluginLoad(PluginAPI_t*);
__declspec(dllexport) void pluginUnload();

#endif