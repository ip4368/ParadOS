
#ifndef _MODULELOADER_TERMINAL_H
#define _MODULELOADER_TERMINAL_H
#include "Types.h"
#include "ModuleLoader/Video.h"
#include "Library/Operations.h"

#define TERMINAL_DEFAULT_COLOR 0xFFFFFF

#define NUMBER_INDEX 16
#define UPPER_INDEX 33
#define LOWER_INDEX 65

class Terminal
{
public:
	void Setup(Video vi);
	void SetXY(uint64 X, uint64 Y);
	void Print(char *text);
	void Print(const char *text, uint32 color);


private:
	void PrintChar(char word, uint32 color);
	Video video;
	uint64 cursorX;
	uint64 cursorY;
};

extern Terminal term;
#endif
