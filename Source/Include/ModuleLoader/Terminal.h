#ifndef _MODULELOADER_TERMINAL_H_
#define _MODULELOADER_TERMINAL_H_

#include "Types.h"

#define TERMINAL_DEFAULT_COLOR 0xFFFFFF

void TerminalSetup();
void SetCursor(uint32 X, uint32 Y);
void SetColor(uint32 c);
void Print(const char *text, ...);

#endif