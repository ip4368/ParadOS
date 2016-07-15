#ifndef _MODULELOADER_GRAPHICS_H_
#define _MODULELOADER_GRAPHICS_H_

#include "Types.h"
	
	void GraphicsSetup(uint32 HR,uint32 VR,uint64 FBB,uint64 FBS, uint32 PPSL, uint8 PF);
	void CleanScreen();
	void CleanScreen(uint32 color);
	void DrawPixel(uint64 x, uint64 y, uint32 color);
	void DrawRectangle(uint64 x, uint64 y, uint32 width, uint32 height, uint32 color);
	bool IsVaildPosition(uint64 x, uint64 y);


uint32 GetHResolution();
uint32 GetVResolution();

#endif
//