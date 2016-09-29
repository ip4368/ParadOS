#include "ModuleLoader/GDT.h"

GDT_PTR *gdt_r;
GDT *gdt;

void SetupGDT(){
	gdt_r = ReadGDT();
	gdt = (GDT *)gdt_r->Base;
	PrintGDT();
}

void PrintGDT(){
	GDT_PTR *temp_r;
	GDT *temp;
	char *selector; 

	temp_r = ReadGDT();

	uint64 cs = 0;
	asm(".intel_syntax noprefix;" "mov rax, cs;" ".att_syntax prefix;" : "=a" (cs));

	uint64 ds = 0;
	asm(".intel_syntax noprefix;" "mov rax, ds;" ".att_syntax prefix;" : "=a" (ds));

	temp = (GDT *)temp_r->Base;
	int count = ((temp_r->Limit + 1) / 8);

	for(uint8 i = 0; i < count;i++){

		if(!i){
			selector = (char *)"NULL";
		}
		if((i * 8) == cs){
			selector = (char *)"CODE";
		}

		if((i*8) == ds){
			selector = (char *)"DATA";
		}

		Print("[%s] LLow: 0x%x BLow: 0x%x BMiddle: 0x%x A: 0x%x G: 0x%x BHigh: 0x%x\n", selector, temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);
	}

}

GDT_PTR* ReadGDT(){
	uint64 *temp;
	asm(".intel_syntax noprefix;" "sgdt [ebx];" ".att_syntax prefix;"::"b" (temp));
	return (GDT_PTR *)temp;
}