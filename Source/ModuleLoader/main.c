#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include "ModuleLoader/BootLoad.h"

extern "C" void main()
{
	
	POS_PAYLOAD *Payload = (POS_PAYLOAD *)PAYLOAD_ADDRESS;
	//Make sure video functional frist, easy to debug.*JK*
	GraphicsSetup(Payload->HResolution, Payload->VResolution, Payload->FrameBufferBase, Payload->FrameBufferSize, Payload->PixelPerScanLine, Payload->ColorFormat);
	TerminalSetup();

	CleanScreen();//Clean sscreen

	//Greeting
	//Customizable Operating System
	Print("Wellcome to ParadOS!\n\n");
	Print("Setting up the hardware...");

	SetupCPU();
	SetColor(0xadff2f);
	Print("done\n");
	Print("pages: %d", Payload->Page_Number);
	HaltCPU();
}

