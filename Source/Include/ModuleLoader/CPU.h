#ifndef _MODULELOADER_CPU_H_
#define _MODULELOADER_CPU_H_

#include "Types.h"
#include "ModuleLoader/Panic.h"
#include "ErrorLevels.h"
#include <cpuid.h>


////Defines////
#define INTEL_CPU 0x00000001
#define AMD_CPU 0x00000002
#define UNKNOWN_CPU 0xffffffff

//CPU Features
#define FPU_SUPPORTED 1 //same as 1 << 0
#define VME_SUPPORTED 1 << 1
#define DE_SUPPORTED 1 << 2
#define PSE_SUPPORTED 1 << 3
#define TSC_SUPPORTED 1 << 4
#define MSR_SUPPORTED 1 << 5 
#define PAE_SUPPORTED 1 << 6
#define MCE_SUPPORTED 1 << 7
#define CX8_SUPPORTED 1 << 8
#define APIC_SUPPORTED 1 << 9
//bit 10 --reserved
#define SEP_SUPPORTED 1 << 11
#define MTRR_SUPPORTED 1 << 12
#define PGE_SUPPORTED 1 << 13
#define MCA_SUPPORTED 1 << 14
#define CMOV_SUPPORTED 1 << 15
#define PAT_SUPPORTED 1 << 16
#define PSE36_SUPPORTED 1 << 17
#define PSN_SUPPORTED 1 << 18
#define CLFSH_SUPPORTED 1 << 19
//bit 20 --reserved
#define DS_SUPPORTED 1 << 21
#define ACPI_SUPPORTED 1 << 22
#define MMX_SUPPORTED 1 << 23
#define FXSR_SUPPORTED 1 << 24
#define SSE_SUPPORTED 1 << 25
#define SSE2_SUPPORTED 1 << 26
#define SS_SUPPORTED 1 << 27
#define HTT_SUPPORTED 1 << 28
#define TM_SUPPORTED 1 << 29
//30-31 --reserved

////Functions////
void InitCPU();

bool SupportCPUID();
bool SupportCPUFeature(uint32 functions);

uint64 GetMSR(uint32 msr_number);

void HaltCPU();

////Variables////
extern uint32 CPU_VENDOR;
extern uint32 CPU_FEATURES;

#endif