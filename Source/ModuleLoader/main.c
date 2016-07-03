#include "Types.h"
#include "ModuleLoader/Video.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"


extern "C" void main()
{

	COS_VIDEO_HEADER *video_hdr = (COS_VIDEO_HEADER *)0x8000;

	//Make sure video functional frist, easy to debug.*JK*
	VideoSetup(video_hdr->HResolution, video_hdr->VResolution, video_hdr->FrameBufferBase, video_hdr->FrameBufferSize, video_hdr->PixelsPerScanLine, video_hdr->PixelFormat);
	TerminalSetup();

	ClearScreen();//Clean sscreen

	//Greeting
	//Customizable Operating System
	Print((char *)"Wellcome to ParadOS!\n\n");
	Print((char *)"Setting up the hardware...");

	SetupCPU();
	Print((char *)"done\n", 0xadff2f);

	HaltCPU();
}

