#include "ModuleLoader/GDT.h"
//extern "C" void GDT_FLUSH();

GDT gdt[3];
GDT_PTR gdt_r;

void SetupGDT(){
	int index  = 0;

	gdt[index].Limit_Low = 0;
	gdt[index].Base_Low = 0;
	gdt[index].Base_Middle = 0;
	gdt[index].Access = 0;
	gdt[index].Granularity = 0;
	gdt[index].Base_High = 0;

	index++;
	gdt[index].Limit_Low = 0xFFFF;
	gdt[index].Base_Low = 0;
	gdt[index].Base_Middle = 0;
	gdt[index].Access = 0x9A;
	gdt[index].Granularity = 0xAF;
	gdt[index].Base_High = 0;

	index++;
	gdt[index].Limit_Low = 0xFFFF;
	gdt[index].Base_Low = 0;
	gdt[index].Base_Middle = 0;
	gdt[index].Access = 0x92;
	gdt[index].Granularity = 0xCF;
	gdt[index].Base_High = 0;

	index++;
	gdt_r.Limit = (8 * index) - 1;
	gdt_r.Base = (uint64)&gdt;

	//GDT_FLUSH();

	PrintGDT();
}

void PrintGDT(){
	GDT_PTR *temp_r;
	GDT *temp;

	temp_r = (GDT_PTR *)ReadGDT();

	Print("GDT Size: %d\n", (temp_r->Limit) + 1);
	temp = (GDT *)temp_r->Base;
	int count = ((temp_r->Limit + 1) / 8);
	Print("GDT Count: %d\n", count);
	for(int i = 0; i < count;i++){
		Print("No.%x:\n LLow: 0x%x BLow: 0x%x BMiddle: 0x%x A: 0x%x G: 0x%x BHigh: 0x%x\n", i * 8, temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);
	}
	uint64 cs = 0;
	asm(".intel_syntax noprefix;" "mov rax, cs;" ".att_syntax prefix;" : "=a" (cs));
	Print("cs: 0x%x\n", cs);
}

uint64* ReadGDT(){
	uint64 *temp;
	asm(".intel_syntax noprefix;" "sgdt [ebx];" ".att_syntax prefix;"::"b" (temp));
	return temp;
}