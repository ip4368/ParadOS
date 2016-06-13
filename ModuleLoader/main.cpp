#include "Types.h"
#include "ModuleLoader/Video.h"
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/CPU.h"


extern "C" void main()
{

	COS_VIDEO_HEADER *video_hdr = (COS_VIDEO_HEADER *)0x7e00;
	
	Video video; //give out the variable

	//Make sure video functional frist, easy to debug.*JK*
	video.Setup(video_hdr->HResolution, video_hdr->VResolution, video_hdr->FrameBufferBase, video_hdr->FrameBufferSize, video_hdr->PixelsPerScanLine, video_hdr->PixelFormat);
	term.Setup(video);

	video.Clear();//Clean sscreen

	//Greeting
	//Customizable Operating System
	term.Print((char *)"Wellcome to Customizable Operating System.\n\n");
	term.Print((char *)"Setting up the hardware...\n");

	SetupCPU();

	REST();
}

