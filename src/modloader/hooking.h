#ifndef HOOKING_H
#define HOOKING_H

void* HookFunction(void* targetFunction, void* hookFunction, size_t hookSize);

#endif