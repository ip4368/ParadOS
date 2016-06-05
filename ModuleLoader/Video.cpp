
#include "ModuleLoader/Video.h"

void Video::Setup(uint32 HR,uint32 VR,uint64 FBB,uint64 FBS, uint32 PPSL, uint8 PF)
{
	FB = (uint32 *)FBB;
	FrameBufferSize = FBS;
	HResolution = HR;
	VResolution = VR;
	PixelsPerScanLine = PPSL;
	PixelFormat = PF;
}

void Video::Clear()
{
	for(uint64 i=0; i<=FrameBufferSize; i++) {
		FB[i] = 0x0;
	}
}
void Video::Clear(uint32 color)
{
	for(uint64 i=0; i<=FrameBufferSize; i++) {
		FB[i] = color;
	}

}

void Video::DrawPixel(uint64 x, uint64 y, uint32 color)
{
	if(IsVaildRange(x, y)) {
		uint64 index = y*PixelsPerScanLine+x;
		FB[index] = color;
	}
}

void Video::DrawRectangle(uint64 x, uint64 y, uint32 width, uint32 height, uint32 color)
{
	if(IsVaildRange(x, y) && IsVaildRange(x + width, y + height)) {
		for(uint64 col = y; col <= height + y; col++) {
			for(uint64 row = x; row <= width + x; row++) {
				DrawPixel(row, col, color);
			}
		}
	}
}

bool Video::IsVaildRange(uint64 x, uint64 y)
{
	if(x > HResolution || y > VResolution) {
		return false;
	} else {
		return true;
	}
}
