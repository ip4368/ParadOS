#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include "ModuleLoader/BootLoad.h"
#include "ModuleLoader/Memory.h"
#include "ModuleLoader/GDT.h"
#include "ModuleLoader/Drawing.h"
//#include "ModuleLoader/Interrupt.h"

//#define WITH_LOGO
#ifdef WITH_LOGO
#include "ModuleLoader/Logo.h"
#endif

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
	
	//put the logo in the middle
	#ifdef WITH_LOGO
	uint32 X = CalculateStartPoint(GetHResolution() /2, WIDTH);
	uint32 Y = CalculateStartPoint(GetVResolution() /2, HEIGTH);
	DrawPicture((uint32 *)&(Logo[0]), X, Y, WIDTH, HEIGTH);
	#endif

	Print("Initializing CPU...\n");
	SetupCPU();

	/*
	Print("Initializing interrupt...\n");
	SetupInterrupt();
	*/
	Print("Initializing GDT...\n");
	SetupGDT();
	
	Print("Initializing Paging...\n");
	Print("MemMap: 0x%x\n", Payload->MemMap);
	PrintMemMap((Payload->MemMap), (Payload->MemMapSize), (Payload->DesSize));

	Print("Resolution: %uw X %uw\n",GetHResolution(), GetVResolution());

	Print("FrameBufferBase: %x\n", Payload->FrameBufferBase);

	/*
	Print("Initializing the interrupt...");
	InitInterrupt();
	*/
	

	HaltCPU();
}

