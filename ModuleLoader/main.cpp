#include "Types.h"
#include "ModuleLoader/Video.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include <cpuid.h>


extern "C" void main(COS_VIDEO_HEADER *video_hdr)
{
	//Make sure video functional frist, easy to debug.*JK*
	Video video;
	video.Setup(video_hdr->HResolution, video_hdr->VResolution, video_hdr->FrameBufferBase, video_hdr->FrameBufferSize, video_hdr->PixelsPerScanLine, video_hdr->PixelFormat);
	Terminal tty(video);
	video.Clear();

	//Say hello
	tty.Print((char *)"Customizable Operating System\n");
	//startup
	//We will keep using this two variable.
	uint32 result;
	//uint32 useless;
	uint32 cpu_string[3];
	//
	//Check is CPUID support though checking the highest function number
	//
	__cpuid(0x0, result, (*cpu_string), (*(cpu_string+1)), (*(cpu_string+2)));
	if(!result){
		//if eax == 0, then CPUID_Support = false;
		tty.Print((char *)"CPUID did not supported.\n");
		goto rest;
	}//support!
	tty.Print((char *)"CPUID supported.\n");
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
/*
	__cpuid(0x80000000, result, useless, useless, useless);
	if(!result){
		//if eax == 0, then CPUID_Ext._Support = false;
		TTY.Print((char *)"CPUID did not supported.\n");
		return false;
	}//support!
	TTY.Print((char *)"CPUID Ext. function supported.\n");
*/

	if(CPU_VENDOR == UNKNOWN_CPU){
		tty.Print((char *)"UNKNOWN_CPU");
	}else if(CPU_VENDOR == INTEL_CPU){
		tty.Print((char *)"INTEL_CPU");
	}else if(CPU_VENDOR == AMD_CPU){
		tty.Print((char *)"AMD_CPU");
	}

rest:
	goto rest;
}

