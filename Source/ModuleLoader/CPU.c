#include "ModuleLoader/CPU.h"

uint32 CPU_VENDOR = 0;
uint32 CPU_FEATURES = 0;


void SetupCPU(){
	//We will keep using this two variable in functions.
	uint32 result = 0;
	uint32 useless = 0;
	uint32 cpu_string[3] = {0,0,0};
	
	//
	//Check is CPUID support though checking the highest function number
	//
	__cpuid(0x0, result, (*cpu_string), (*(cpu_string+1)), (*(cpu_string+2)));
	if(!result){
		//if eax == 0, then CPUID_Support = false;
		SetColor(0xff0000);
		Print("CPUID is not supported.\n");
		HaltCPU();
	}//support!

	//
	//Get CPU Vendor ID
	//
	if(cpu_string[0] == signature_INTEL_ebx && cpu_string[1] == signature_INTEL_ecx && cpu_string[2] == signature_INTEL_edx){//Intel cpu?
		CPU_VENDOR = INTEL_CPU;
	}else if(cpu_string[0] == signature_AMD_ebx && cpu_string[1] == signature_AMD_ecx && cpu_string[2] == signature_AMD_edx){//AMD cpu?
		CPU_VENDOR = AMD_CPU;
	}else{//nah IDK
		CPU_VENDOR = UNKNOWN_CPU;
	}

	//
	//Check is CPU support Ext. function.
	//
	__cpuid(0x80000000, result, useless, useless, useless);
	if(!result){
		//if eax == 0, then CPUID_Ext._Support = false;
		SetColor(0xff0000);
		Print("CPUID Ext. is not supported.\n");
		HaltCPU();
	}//support!

	//
	//Get CPU feature flag
	//
	__cpuid(0x1, useless, useless, useless, CPU_FEATURES); //we only need edx
	if(CPU_FEATURES == 0){
		SetColor(0xff0000);
		Print("Cant get cpu feature flags.\n");
		HaltCPU();	
	}

	//
	//Support MSR?
	//
	if(!(CPU_FEATURES & MSR_SUPPORTED)){
		SetColor(0xff0000);
		Print("MSR is not supported.\n");
		HaltCPU();	
	}

	uint64 msr = GetMSR(0xc0000080);
	if(msr & 1<<10){//lma
		Print("Long mode active\n");
	}else{
		SetColor(0xff0000);
		Print("Long mode was not actived\n");
		HaltCPU();
	}

}

uint64 GetMSR(uint32 msr_number){

	uint32 lower = 0;
	uint32 higher = 0;
	uint64 result = 0;
	__asm__ ("rdmsr\n\t" : "=a"(lower), "=d"(higher) : "c"(msr_number));
	result = (higher <<  31) | lower;
	return result;
}

void HaltCPU(){
	//disable interrupt
	__asm__("cli");
	for(;;){
		__asm__("hlt");
	}
}	
