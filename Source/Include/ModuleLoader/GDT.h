#ifndef _MODULELOADER_GDT_H_
#define _MODULELOADER_GDT_H_
#include "Types.h"
#include "ModuleLoader/Terminal.h"

typedef struct {
	uint16 Limit_Low;
	uint16 Base_Low;
	uint8 Base_Middle;
	uint8 Access;
	uint8 Granularity;
	uint8 Base_High;
} __attribute__((packed)) GDT;

typedef struct {
	uint16 Limit;
	uint64 Base;
} __attribute__((packed)) GDT_PTR;

void SetupGDT();
void PrintGDT();
GDT_PTR* ReadGDT();
#endif