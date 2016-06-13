#ifndef _MODULELOADER_CPU_H
#define _MODULELOADER_CPU_H
#include "Types.h"
#include "ModuleLoader/Panic.h"
#include "ErrorLevels.h"
#include <cpuid.h>

extern "C" void REST();
extern "C" void BRAIN_WASHING();

//defines
#define INTEL_CPU 0x00000001
#define AMD_CPU 0x00000002
#define UNKNOWN_CPU 0xffffffff

//functions
void SetupCPU();
#endif