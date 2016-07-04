#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"


extern "C" void main()
{

	COS_GRAPHICS_HEADER *Graphics_hdr = (COS_GRAPHICS_HEADER *)0x8000;

	//Make sure video functional frist, easy to debug.*JK*
	GraphicsSetup(Graphics_hdr->HResolution, Graphics_hdr->VResolution, Graphics_hdr->FrameBufferBase, Graphics_hdr->FrameBufferSize, Graphics_hdr->PixelsPerScanLine, Graphics_hdr->PixelFormat);
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

