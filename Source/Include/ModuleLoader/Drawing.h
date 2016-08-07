#ifndef _MODULELOADER_DRAWING_H_
#define _MODULELOADER_DRAWING_H_
#include "Types.h"
#include "ModuleLoader/Graphics.h"

#include "ModuleLoader/Terminal.h"

uint32 DrawPicture(uint32 *picture, uint32 x, uint32 y, uint32 width, uint32 height);
uint32 CalculateStartPoint(uint32 pos, uint32 length);

#endif