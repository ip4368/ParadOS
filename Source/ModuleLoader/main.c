#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include "ModuleLoader/BootLoad.h"
#include "ModuleLoader/Memory.h"
#include "ModuleLoader/GDT.h"
#include "ModuleLoader/Logo.h"
#include "ModuleLoader/Drawing.h"

extern "C" void main()
{
	
	POS_PAYLOAD *Payload = (POS_PAYLOAD *)PAYLOAD_ADDRESS;
	//Make sure video functional frist, easy to debug.*JK* //uefi framebufferbase = c0000000
	SetupGraphics(Payload->HResolution, Payload->VResolution, Payload->FrameBufferBase, Payload->FrameBufferSize, Payload->PixelPerScanLine, Payload->ColorFormat);
	SetupTerminal();

	//Greeting
	//Customizable Operating System
	CleanScreen();//Clean sscreen
	
	Print("Wellcome to ParadOS!\n\n");
	/*
	//put the logo in the middle
	uint32 X = CalculateStartPoint(GetHResolution() /2, WIDTH);
	uint32 Y = CalculateStartPoint(GetVResolution() /2, HEIGTH);
	DrawPicture((uint32 *)&(Logo[0]), X, Y, WIDTH, HEIGTH);
*/	
/*
	Print("Initializing the Paging...\n");
	SetupPaging();
	*/

	Print("Initializing the GDT...\n");
	SetupGDT();


	Print("Initializing the CPU...\n");
	SetupCPU();
	Print("Resolution: %uw X %uw\n",GetHResolution(), GetVResolution());

	Print("FrameBufferBase: %x\n", Payload->FrameBufferBase);

/*
	Print("Initializing the interrupt...");
	InitInterrupt();
	*/
	

	HaltCPU();
}

