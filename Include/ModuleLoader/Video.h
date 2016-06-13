
#ifndef _MODULELOADER_VIDEO_H
#define _MODULELOADER_VIDEO_H
#include "Types.h"

class Video
{
public:

	void Setup(uint32 HR,uint32 VR,uint64 FBB,uint64 FBS, uint32 PPSL, uint8 PF);
	void DrawPixel(uint64 x, uint64 y, uint32 color);
	void DrawRectangle(uint64 x, uint64 y, uint32 width, uint32 height, uint32 color);
	void Clear();
	void Clear(uint32 color);
	bool IsVaildRange(uint64 x, uint64 y);
private:
	uint32 *FB;
	uint32 HResolution;
	uint32 VResolution;
	uint64 FrameBufferSize;
	uint32 PixelsPerScanLine;
	uint8 PixelFormat;
};

typedef struct {
	uint32 HResolution;
	uint32 VResolution;
	uint64 FrameBufferBase;
	uint64 FrameBufferSize;
	uint32 PixelsPerScanLine;
	uint8 PixelFormat;

} COS_VIDEO_HEADER;


#endif
