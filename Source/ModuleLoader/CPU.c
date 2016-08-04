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
		Panic((char *)"CPUID did not supported.\n", PANIC_LEVEL_TWO);
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
		Panic((char *)"CPUID Ext. did not supported.\n", PANIC_LEVEL_TWO);
		HaltCPU();
	}//support!

	//
	//If the system enter in normal way(uefi), 
	//it will enter long mode and paging enabled. 
	//But we need to check that and make sure everything is ok
	//
	__cpuid(0x80000001, useless, useless, useless, result);
	if(!(result & bit_LM)){ //Thanks for the cpuid.h, make me work ez
		//Well..not the normal way.
		Panic((char *)"Omfg! You are not in long mode!\n", PANIC_LEVEL_TWO);
		HaltCPU();
	}//We are in long mode

	//
	//Get CPU feature flag
	//
	__cpuid(0x1, useless, useless, useless, CPU_FEATURES); //we only need edx
	if(CPU_FEATURES == 0){
		Panic((char *)"Cant get cpu feature flags.\n", PANIC_LEVEL_TWO);
		HaltCPU();
	}	

}

uint64 GetMSR(uint32 msr_number){

	uint32 lower = 0;
	uint32 higher = 0;
	uint64 result = 0;
	if(CPU_FEATURES & MSR_SUPPORTED){ //MSR supported
		__asm__ ("rdmsr\n\t" : "=a"(lower), "=d"(higher) : "c"(msr_number));
		result = (higher <<  31) | lower;
		return result;
	}else{
		return 0;
	}
}

void HaltCPU(){
	//disable interrupt
	__asm__("cli");
	for(;;);
}	