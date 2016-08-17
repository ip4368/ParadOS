#include "ModuleLoader/Memory.h"
#include "ModuleLoader/Terminal.h"
uint64 PDP[4] __attribute__((aligned(0x1000)));
uint64 PD[512] __attribute__((aligned(0x1000)));
uint64 PT[512] __attribute__((aligned(0x1000)));

void SetupPaging(){

	uint64 cr = 0;
	asm(".intel_syntax noprefix;" "xor rax, rax;" "mov rax, cr0;" ".att_syntax prefix;" :"=a" (cr));
	cr = cr & 0x7fffffff;
	asm(".intel_syntax noprefix;" "mov cr0, rax;" ".att_syntax prefix;": :"a" (cr));

	//wipe memory area
	for(int i = 0; i < 4; i++){
		PDP[i] = 0;
	}
	for(int i = 0; i < 512; i++){
		PD[i] = 0;
		PT[i] = 0;
	}
	//pointing
	PDP[0] = (uint64)&PD | 1;
	PD[0] = (uint64)&PT | 3;

	uint32 PageSize = 0;
	for(int i = 0; i < 512; i++){
		PT[i] = PageSize | 3;
		PageSize += 4096;
	}

	asm(".intel_syntax noprefix;" "mov cr3, rax;" ".att_syntax prefix;" : : "a" (&PDP));	

	asm(".intel_syntax noprefix;" "xor rax, rax;" "mov rax, cr0;" ".att_syntax prefix;" :"=a" (cr));
	cr += 0x80000000;
	asm(".intel_syntax noprefix;" "mov cr0, rax;" ".att_syntax prefix;": :"a" (cr));


}