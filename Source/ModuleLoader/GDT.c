#include "ModuleLoader/GDT.h"

GDT_PTR *gdt_r;
GDT *gdt;

void SetupGDT(){
	gdt_r = ReadGDT();
	gdt = (GDT *)gdt_r->Base;
}

void PrintGDT(){
	GDT_PTR *temp_r;
	GDT *temp;

	temp_r = ReadGDT();

	Print("GDT Size: %d\n", (temp_r->Limit) + 1);
	temp = (GDT *)temp_r->Base;
	int count = ((temp_r->Limit + 1) / 8);
	Print("GDT Count: %d\n", count);
	for(int i = 0; i < count;i++){
		Print("No. 0x%x:\n LLow: 0x%x BLow: 0x%x BMiddle: 0x%x A: 0x%x G: 0x%x BHigh: 0x%x\n", i * 8, temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);
	}
	uint64 cs = 0;
	asm(".intel_syntax noprefix;" "mov rax, cs;" ".att_syntax prefix;" : "=a" (cs));
	Print("cs: 0x%x\n", cs);
}

GDT_PTR* ReadGDT(){
	uint64 *temp;
	asm(".intel_syntax noprefix;" "sgdt [ebx];" ".att_syntax prefix;"::"b" (temp));
	return (GDT_PTR *)temp;
}