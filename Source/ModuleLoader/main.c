#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"


extern "C" void main()
{

	COS_GRAPHICS_HEADER *graphics_hdr = (COS_GRAPHICS_HEADER *)0x8000;

	//Make sure video functional frist, easy to debug.*JK*
	GraphicsSetup(graphics_hdr->HResolution, graphics_hdr->VResolution, graphics_hdr->FrameBufferBase, graphics_hdr->FrameBufferSize, graphics_hdr->PixelsPerScanLine, graphics_hdr->PixelFormat);
	TerminalSetup();

	CleanScreen();//Clean sscreen

	//Greeting
	//Customizable Operating System
	Print((char *)"Wellcome to ParadOS!\n\n");
	Print((char *)"Setting up the hardware...");

	SetupCPU();
	Print((char *)"done\n", 0xadff2f);

	HaltCPU();
}

