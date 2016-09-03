#include "ModuleLoader/Memory.h"
#include "ModuleLoader/Terminal.h"

const char *MemMapType[] = { 
    "ReservedMemory         ", 
    "LoaderCode             ", 
    "LoaderData             ", 
    "BootServicesCode       ", 
    "BootServicesData       ", 
    "RuntimeServicesCode    ", 
    "RuntimeServicesData    ", 
    "ConventionalMemory     ", 
    "UnusableMemory         ", 
    "ACPIReclaimMemory      ", 
    "ACPIMemoryNVS          ", 
    "MemoryMappedIO         ", 
    "MemoryMappedIOPortSpace", 
    "PalCode                ", 
    "MaxMemory              "
};

void SetupPaging(EFI_MEMORY_DESCRIPTOR *MemMap, uint64 MemMapSize, uint64 DesSize){
	//uint64 *PDP = (uint64 *)0X1000;
	//uint64 *PD = (uint64 *)0X2000;
	//uint64 *PT = (uint64 *)0X3000;

	PrintMemMap(MemMap, MemMapSize, DesSize);
	//wipe memory area

	
	//asm(".intel_syntax noprefix;" "mov cr3, rax;" ".att_syntax prefix;" : : "a" (&PDP));	

	
}

void PrintMemMap(EFI_MEMORY_DESCRIPTOR* MemMap, uint64 MemMapSize, uint64 DesSize){
	EFI_MEMORY_DESCRIPTOR* map = MemMap;
	uint64 max = (MemMapSize) / (DesSize);
	for(uint64 i = 0; i < max; i++){
	EFI_MEMORY_DESCRIPTOR *temp = (EFI_MEMORY_DESCRIPTOR *)(((uint8 *)map) + (i * DesSize));
	Print("[#%uq] Type: %s Phy: 0x%x-0x%x Virt: 0x%x Page: %uq\n", i, MemMapType[temp->Type], temp->PhysicalStart, ((temp->PhysicalStart) + ((temp->NumberOfPages) * 4096) - 1), temp->VirtualStart, temp->NumberOfPages);
	}
}

void EnablePaging(){
	uint64 cr = 0;
	asm(".intel_syntax noprefix;" "xor rax, rax;" "mov rax, cr0;" ".att_syntax prefix;" :"=a" (cr));
	cr += 0x80000000;
	asm(".intel_syntax noprefix;" "mov cr0, rax;" ".att_syntax prefix;": :"a" (cr));
}

void DisablePaging(){
	uint64 cr = 0;
	asm(".intel_syntax noprefix;" "xor rax, rax;" "mov rax, cr0;" ".att_syntax prefix;" :"=a" (cr));
	cr = cr & 0x7fffffff;
	asm(".intel_syntax noprefix;" "mov cr0, rax;" ".att_syntax prefix;": :"a" (cr));
}