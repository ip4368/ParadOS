#include "ModuleLoader/Memory.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/BootLoad.h"
#include "Library/Size.h"

	uint64 *PDP;
	uint64 TotalPage = 0;
	uint64 TotalMemory = 0;
	uint64 ReservedMemory, LoaderCode, LoaderData, BootServicesCode, BootServicesData, RuntimeServicesCode, RuntimeServicesData,ConventionalMemory, UnusableMemory, ACPIMemoryNVS, ACPIReclaimMemory, MemoryMappedIO, MemoryMappedIOPortSpace;


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
/*
enum POSMemMapType{
	UNUSABLE_MEMORY = 0,
	AVAILABLE_MEMORY,
	SYSTEM_MEMORY,
	USER_MEMORY
};

const char *POSMemMapTypeText[] = {
	"UnusableMemory",
	"AvailsableMemory",
	"SystemMemory",
	"UserMemory"
};
*/

void SetupPaging(EFI_MEMORY_DESCRIPTOR *MemMap, uint64 MemMapSize, uint64 DesSize, uint64 MLSize){
	
	ParseMemMap(MemMap, MemMapSize, DesSize);
	//UEFI has setting up PAE for us, so no need to relocate the page table.
	//TODO: We know the where are the page table is and got the memory map.
	Print("\nReservedMemory: %u\n", ReservedMemory);
	Print("LoaderCode: %u\n", LoaderCode);
	Print("LoaderData: %u\n", LoaderData);
	Print("BootServicesCode: %u\n", BootServicesCode);
	Print("BootServicesData: %u\n", BootServicesData);
	Print("RuntimeServicesCode: %u\n", RuntimeServicesCode);
	Print("RuntimeServicesData: %u\n", RuntimeServicesData);
	Print("ConventionalMemory: %u\n", ConventionalMemory);
	Print("UnusableMemory: %u\n", UnusableMemory);
	Print("ACPIMemoryNVS: %u\n", ACPIMemoryNVS);
	Print("ACPIReclaimMemory: %u\n", ACPIReclaimMemory);
	Print("MemoryMappedIO: %u\n", MemoryMappedIO);
	Print("MemoryMappedIOPortSpace: %u\n", MemoryMappedIOPortSpace);
	
	TotalMemory = ReservedMemory + LoaderCode + LoaderData + BootServicesCode + BootServicesData + RuntimeServicesCode + RuntimeServicesData + ConventionalMemory + UnusableMemory + ACPIReclaimMemory + ACPIMemoryNVS + MemoryMappedIO + MemoryMappedIOPortSpace;
	TotalMemory *= 4096;
	uint64 converted = SizeConvert(TotalMemory, SIZE_BASE_MB);
	Print("TotalMemory: %u MB\n", converted);

	uint64 MLPage = MLSize /4096;
	Print("MLSize: %u\n", MLSize);
	Print("MLPage: %u\n", MLPage);
}

void ParseMemMap(EFI_MEMORY_DESCRIPTOR* MemMap, uint64 MemMapSize, uint64 DesSize){
	EFI_MEMORY_DESCRIPTOR* map = MemMap;
	uint64 max = MemMapSize / DesSize;
	for(uint64 i = 0; i < max; i++){
	EFI_MEMORY_DESCRIPTOR *temp = (EFI_MEMORY_DESCRIPTOR *)(((uint8 *)map) + (i * DesSize));
	if(temp->NumberOfPages != 0){
	Print("[#%d] Type: %s Phy: 0x%x-0x%x Virt: 0x%x Page: %u\n", i, MemMapType[temp->Type], temp->PhysicalStart, ((temp->PhysicalStart) + ((temp->NumberOfPages) * 4096) - 1), temp->VirtualStart, temp->NumberOfPages);
	switch(temp->Type){
		case 0://ReservedMemory
			ReservedMemory += temp->NumberOfPages;
			break;
		case 1://LoaderCode
			LoaderCode += temp->NumberOfPages;
			break;
		case 2://LoaderData
			LoaderData += temp->NumberOfPages;
			break;
		case 3://BootServicesCode
			BootServicesCode += temp->NumberOfPages;
			break;
		case 4: //BootServicesData
			BootServicesData += temp->NumberOfPages;
			break;
		case 5://RuntimeServicesCode
			RuntimeServicesCode += temp->NumberOfPages;
			break;
		case 6://RuntimeServicesData
			RuntimeServicesData += temp->NumberOfPages;
			break;
		case 7://ConventionalMemory
			ConventionalMemory += temp->NumberOfPages;
			break;
		case 8://UnusableMemory
			UnusableMemory += temp->NumberOfPages;
			break;
		case 9://ACPIReclaimMemory
			ACPIReclaimMemory += temp->NumberOfPages;
			break;
		case 10://ACPIMemoryNVS
			ACPIMemoryNVS += temp->NumberOfPages;
			break;
		case 11://MemoryMappedIO
			MemoryMappedIO += temp->NumberOfPages;
			break;
		case 12://MemoryMappedIOPortSpace
			MemoryMappedIOPortSpace += temp->NumberOfPages;
			break;
		default:
			break;
		}
	}
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

void FlushPageTable(){
	asm(".intel_syntax noprefix;" "mov cr3, rax;" ".att_syntax prefix;" : : "a" (&PDP));
}