#ifndef _MODULELOADER_MEMORY_H_
#define _MODULELOADER_MEMORY_H_
#include "Types.h"
#include "ModuleLoader/BootLoad.h"

typedef enum {
EfiReservedMemoryType,
EfiLoaderCode,
EfiLoaderData,
EfiBootServicesCode,
EfiBootServicesData,
EfiRuntimeServicesCode,
EfiRuntimeServicesData,
EfiConventionalMemory,
EfiUnusableMemory,
EfiACPIReclaimMemory,
EfiACPIMemoryNVS,
EfiMemoryMappedIO,
EfiMemoryMappedIOPortSpace,
EfiPalCode,
EfiPersistentMemory,
EfiMaxMemoryType
} EFI_MEMORY_TYPE;



void SetupPaging(EFI_MEMORY_DESCRIPTOR *MemMap, uint64 MemMapSize, uint64 DesSize, uint64 MLPage);
void ParseMemMap(EFI_MEMORY_DESCRIPTOR* MemMap, uint64 MemMapSize, uint64 DesSize);
void EnablePaging();
void DisablePaging();

#endif