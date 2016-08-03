#include "Types.h"
#include "ModuleLoader/Graphics.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"


typedef struct {
	uint32 HResolution;
	uint32 VResolution;
	uint64 FrameBufferBase;
	uint64 FrameBufferSize;
	uint32 PixelsPerScanLine;
	uint8 PixelFormat;
} POS_GRAPHICS_INFO;


typedef struct 
{
	POS_GRAPHICS_INFO *GraphicsInfo; 
	
}POS_BOOTLOADER_HEADER; 

extern "C" void main(uint64 pageNumber)
{

	POS_BOOTLOADER_HEADER *bootloader_hdr = (POS_BOOTLOADER_HEADER *)0x8000;
	POS_GRAPHICS_INFO *graphics_info = bootloader_hdr->GraphicsInfo;
	//Make sure video functional frist, easy to debug.*JK*
	InitGraphics(graphics_info->HResolution, graphics_info->VResolution, graphics_info->FrameBufferBase, graphics_info->FrameBufferSize, graphics_info->PixelsPerScanLine, graphics_info->PixelFormat);
	InitTerminal();

	CleanScreen();//Clean sscreen

	//Greeting
	//Customizable Operating System
	Print("Wellcome to ParadOS!\n\n");
	Print("Setting up the hardware...");

	InitCPU();
	SetColor(0xadff2f);
	Print("done\n");
	SetColor(TERMINAL_DEFAULT_COLOR);
	if(pageNumber > 0){
		Print("bigger");
	}
	HaltCPU();
}

