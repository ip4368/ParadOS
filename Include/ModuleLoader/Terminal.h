#ifndef _MODULELOADER_TERMINAL_H_
#define _MODULELOADER_TERMINAL_H_

#include "Types.h"

void TerminalSetup();
void SetCursor(uint64 X, uint64 Y);
void Print(char *text);
void Print(const char *text, uint32 color);

#endif