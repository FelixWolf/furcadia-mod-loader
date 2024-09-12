#include <windows.h>
#include <cstring>
#include <cstdio>
#include "hooking.h"

// Hooking function, but now with proper size handling
void* HookFunction(void* targetFunction, void* hookFunction, size_t hookSize)
{
    DWORD oldProtect;
    if (!VirtualProtect(targetFunction, hookSize, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        printf("Failed to set memory protection.\n");
        return nullptr;
    }

    // Allocate space for the trampoline, which includes the original instructions and a JMP back
    BYTE* trampoline = (BYTE*)VirtualAlloc(NULL, hookSize + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!trampoline)
    {
        printf("Failed to allocate memory for the trampoline.\n");
        return nullptr;
    }

    // Copy the original instructions to the trampoline
    memcpy(trampoline, targetFunction, hookSize);

    // Calculate the relative jump from the trampoline to the original function after the hook
    DWORD relativeAddress = (DWORD)targetFunction + hookSize - ((DWORD)trampoline + hookSize + 5);
    trampoline[hookSize] = 0xE9; // JMP opcode
    memcpy(trampoline + hookSize + 1, &relativeAddress, sizeof(relativeAddress));

    // Overwrite the target function with the JMP to our hook
    BYTE jumpInstruction[5] = { 0xE9 };
    relativeAddress = (DWORD)hookFunction - ((DWORD)targetFunction + 5);
    memcpy(jumpInstruction + 1, &relativeAddress, sizeof(relativeAddress));
    memcpy(targetFunction, jumpInstruction, sizeof(jumpInstruction));

    // NOP the remaining byte (if we’re overwriting more than 5 bytes)
    if (hookSize > 5)
    {
        memset((BYTE*)targetFunction + 5, 0x90, hookSize - 5); // NOP the rest
    }

    // Restore the original protection
    if (!VirtualProtect(targetFunction, hookSize, oldProtect, &oldProtect))
    {
        printf("Failed to restore memory protection.\n");
        return nullptr;
    }

    return trampoline;
}

/*
typedef void(__fastcall *HandleProtocolMessage_t)(char*);
HandleProtocolMessage_t originalHandleProtocolMessage = nullptr;

// Hooked function
void __fastcall MyHandleProtocolMessage(char *param_1) {
    printf("Intercepted message: %s\n", param_1);
    // Call the original function via trampoline
    originalHandleProtocolMessage(param_1);
}
*/
