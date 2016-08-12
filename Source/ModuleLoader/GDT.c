#include "ModuleLoader/GDT.h"

void SetupGDT(){
	PrintGDT();
}

void PrintGDT(){
	GDT_PTR *temp_r;
	GDT *temp;

	temp_r = (GDT_PTR *)ReadGDT();

	Print("GDT Size: %d\n", temp_r->Limit);
	temp = (GDT *)temp_r->Base;
	int i = 0;
	Print("NULL:\n Limit_Low: 0x%x\n Base_Low: 0x%x\n Base_Middle: 0x%x\n Access: 0x%x\n Granularity: 0x%x\n Base_High: 0x%x\n", temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);
	i++;
	Print("CODE:\n Limit_Low: 0x%x\n Base_Low: 0x%x\n Base_Middle: 0x%x\n Access: 0x%x\n Granularity: 0x%x\n Base_High: 0x%x\n", temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);
	i++;
	Print("DATA:\n Limit_Low: 0x%x\n Base_Low: 0x%x\n Base_Middle: 0x%x\n Access: 0x%x\n Granularity: 0x%x\n Base_High: 0x%x\n", temp[i].Limit_Low, temp[i].Base_Low, temp[i].Base_Middle, temp[i].Access, temp[i].Granularity, temp[i].Base_High);

	uint64 cs = 0;
	asm(".intel_syntax noprefix;" "mov rax, cs;" ".att_syntax prefix;" : "=a" (cs));
	Print("cs: 0x%x\n", cs);
}

uint64* ReadGDT(){
	uint64 *temp;
	asm(".intel_syntax noprefix;" "sgdt [ebx];" ".att_syntax prefix;"::"b" (temp));
	return temp;
}