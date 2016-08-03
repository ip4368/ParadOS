#include "Moduleloader/PIC.h"

void InitAPIC(){
	//
	//Check APIC availbale
	//
	if(!(CPU_FEATURES & APIC_SUPPORTED)){
		Panic((char *)"APIC is not support.", PANIC_LEVEL_TWO);
		HaltCPU();
	}
}