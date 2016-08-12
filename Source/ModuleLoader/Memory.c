#include "ModuleLoader/Memory.h"

//uint64 PML4T[4] __attribute__((aligned(0x1000)));
//uint64 PDPT[512] __attribute__((aligned(0x1000)));
//uint64 PDT[512] __attribute__((aligned(0x1000)));
//uint64 PT[512] __attribute__((aligned(0x1000)));

void SetupPaging(){
/*
	//wipe memory area
	for(int i = 0; i < 4; i++){
		PML4T[i] = 0;
	}
	for(int i = 0; i < 512; i++){
		PDPT[i] = 0;
		PDT[i] = 0;
		PT[i] = 0;
	}
	//pointing
	PML4T[0] = (uint64)&PDPT;
	PDPT[0] = (uint64)&PDT;
	PDT[0] = (uint64)&PT;

	PDPT[0] |= 3;
	PDT[0] |= 3;

	uint32 PageSize = 0;
	for(int i = 0; i < 512; i++){
		PT[i] = PageSize | 3;
		PageSize += 4096;
	}

	asm(".intel_syntax noprefix;" "mov cr3, rax;" ".att_syntax prefix;" : : "a" (&PML4T));
	*/
}