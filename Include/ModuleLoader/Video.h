#ifndef _MODULELOADER_VIDEO_H_
#define _MODULELOADER_VIDEO_H_

#include "Types.h"
	
	void VideoSetup(uint32 HR,uint32 VR,uint64 FBB,uint64 FBS, uint32 PPSL, uint8 PF);
	void ClearScreen();
	void VideoScreen(uint32 color);
	void DrawPixel(uint64 x, uint64 y, uint32 color);
	void DrawRectangle(uint64 x, uint64 y, uint32 width, uint32 height, uint32 color);
	bool IsVaildPosition(uint64 x, uint64 y);

typedef struct {
	uint32 HResolution;
	uint32 VResolution;
	uint64 FrameBufferBase;
	uint64 FrameBufferSize;
	uint32 PixelsPerScanLine;
	uint8 PixelFormat;

} COS_VIDEO_HEADER;

#endif