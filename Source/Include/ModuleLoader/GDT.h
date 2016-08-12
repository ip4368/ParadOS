#ifndef _MODULELOADER_GDT_H_
#define _MODULELOADER_GDT_H_
#include "Types.h"
#include "ModuleLoader/Terminal.h"
#pragma pack(1)
struct GDT{
	uint16 Limit_Low;
	uint16 Base_Low;
	uint8 Base_Middle;
	uint8 Access;
	uint8 Granularity;
	uint8 Base_High;
};
struct GDT_PTR{
	uint16 Limit;
	uint64 Base;
};
#pragma pack()
void SetupGDT();
void PrintGDT();
uint64* ReadGDT();
#endif