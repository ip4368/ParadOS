#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include "ModuleLoader/BootLoad.h"
#include "ModuleLoader/Logo.h"
#include "ModuleLoader/Drawing.h"

extern "C" void main()
{
	
	POS_PAYLOAD *Payload = (POS_PAYLOAD *)PAYLOAD_ADDRESS;
	//Make sure video functional frist, easy to debug.*JK*
	SetupGraphics(Payload->HResolution, Payload->VResolution, Payload->FrameBufferBase, Payload->FrameBufferSize, Payload->PixelPerScanLine, Payload->ColorFormat);
	SetupTerminal();

	//Greeting
	//Customizable Operating System
	CleanScreen();//Clean sscreen

	
	Print("Wellcome to ParadOS!\n\n");

	Print("Initializing the CPU...");
	SetupCPU();
	SetColor(0xadff2f);
	Print("done\n");
	Print("Resolution: %d X %d\n",GetHResolution(), GetVResolution());


/*
	Print("Initializing the interrupt...");
	InitInterrupt();
	*/

	//put the logo in the middle
	
	uint32 X = CalculateStartPoint(GetHResolution() / 2, WIDTH);
	uint32 Y = CalculateStartPoint(GetVResolution() / 2, HEIGTH);
	DrawPicture((uint32 *)&(Logo[0]), X, Y, WIDTH, HEIGTH);
	

	HaltCPU();
}

