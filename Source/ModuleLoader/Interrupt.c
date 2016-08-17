#include "ModuleLoader/Interrupt.h"
#include "ModuleLoader/CPU.h"

void SetupInterrupt(){
	//check is APIC available
	if(CPU_FEATURES & APIC_SUPPORTED){

	}else{
		
	}
}