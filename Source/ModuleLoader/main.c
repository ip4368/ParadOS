#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"
#include "ModuleLoader/BootLoad.h"
#include "ModuleLoader/Memory.h"
#include "ModuleLoader/GDT.h"
#include "ModuleLoader/Logo.h"
#include "ModuleLoader/Drawing.h"
//#include "ModuleLoader/Interrupt.h"

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
	
	//put the logo in the middle
	uint32 X = CalculateStartPoint(GetHResolution() /2, WIDTH);
	uint32 Y = CalculateStartPoint(GetVResolution() /2, HEIGTH);
	DrawPicture((uint32 *)&(Logo[0]), X, Y, WIDTH, HEIGTH);
<<<<<<< HEAD

=======
>>>>>>> master
	Print("Initializing CPU...\n");
	SetupCPU();

	EFI_MEMORY_DESCRIPTOR* map = Payload->MemMap;
	Print("MemMapSize: %d\n", Payload->MemMapSize);
	Print("DesSize: %d\n", Payload->DesSize);
	uint64 max = (Payload->MemMapSize) / (Payload->DesSize);
	for(uint64 i = 0; i < max; i++){
	EFI_MEMORY_DESCRIPTOR *temp = (EFI_MEMORY_DESCRIPTOR *)(((uint8 *)map) + (i * Payload->DesSize));
	Print("[#%uq] Type: %s Phy: 0x%x-0x%x Page: %uq\n", i, memory_types[temp->Type], temp->PhysicalStart, ((temp->PhysicalStart) + ((temp->NumberOfPages) * 4096) - 1), temp->NumberOfPages);
	}

/*
	Print("Initializing interrupt...\n");
	SetupInterrupt();
	*/
	/*
	Print("Initializing the Paging...\n");
	SetupPaging();
	*/

//	Print("Initializing GDT...\n");
//	SetupGDT();

	Print("Resolution: %uw X %uw\n",GetHResolution(), GetVResolution());

	Print("FrameBufferBase: %x\n", Payload->FrameBufferBase);

/*
	Print("Initializing the interrupt...");
	InitInterrupt();
	*/
	

	HaltCPU();
}

