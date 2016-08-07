#ifndef _MODULELOADER_FONT_H_
#define _MODULELOADER_FONT_H_

#include "Types.h"

/*
Come from vincent font
*/
uint8 Font_Data[95][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18 },
	{ 0x00, 0x36, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36 },
	{ 0x00, 0x08, 0x1E, 0x20, 0x1C, 0x02, 0x3C, 0x08 },
	{ 0x00, 0x60, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x06 },
	{ 0x00, 0x3C, 0x66, 0x3C, 0x28, 0x65, 0x66, 0x3F },
	{ 0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00 },
	{ 0x00, 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60 },
	{ 0x00, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06 },//10
	{ 0x00, 0x00, 0x36, 0x1C, 0x7F, 0x1C, 0x36, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x60 },
	{ 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60 },
	{ 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00 },
	{ 0x00, 0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C },
	{ 0x00, 0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E },
	{ 0x00, 0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E },
	{ 0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C },
	{ 0x00, 0x0C, 0x1C, 0x2C, 0x4C, 0x7E, 0x0C, 0x0C },
	{ 0x00, 0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C },
	{ 0x00, 0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C },
	{ 0x00, 0x7E, 0x66, 0x0C, 0x0C, 0x18, 0x18, 0x18 },
	{ 0x00, 0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C },
	{ 0x00, 0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C },
	{ 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00 },
	{ 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30 },
	{ 0x00, 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06 },
	{ 0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60 },
	{ 0x00, 0x3C, 0x66, 0x06, 0x1C, 0x18, 0x00, 0x18 },
	{ 0x00, 0x38, 0x44, 0x5C, 0x58, 0x42, 0x3C, 0x00 },
	{ 0x00, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66 },
	{ 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C },
	{ 0x00, 0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C },
	{ 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C },
	{ 0x00, 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E },
	{ 0x00, 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60 },
	{ 0x00, 0x3C, 0x66, 0x60, 0x60, 0x6E, 0x66, 0x3C },
	{ 0x00, 0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66 },
	{ 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C },
	{ 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38 },
	{ 0x00, 0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66 },
	{ 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E },
	{ 0x00, 0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63 },
	{ 0x00, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x63, 0x63 },
	{ 0x00, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C },
	{ 0x00, 0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60 },
	{ 0x00, 0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x06 },
	{ 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66 },
	{ 0x00, 0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C },
	{ 0x00, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E },
	{ 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18 },
	{ 0x00, 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63 },
	{ 0x00, 0x63, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x63 },
	{ 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18 },
	{ 0x00, 0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E },
	{ 0x00, 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E },
	{ 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00 },
	{ 0x00, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78 },
	{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F },
	{ 0x00, 0x0C, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E },
	{ 0x00, 0x60, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C },
	{ 0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C },
	{ 0x00, 0x06, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3E },
	{ 0x00, 0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C },
	{ 0x00, 0x1C, 0x36, 0x30, 0x30, 0x7C, 0x30, 0x30 },
	{ 0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x3C },
	{ 0x00, 0x60, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66 },
	{ 0x00, 0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x3C },
	{ 0x00, 0x0C, 0x00, 0x0C, 0x0C, 0x6C, 0x6C, 0x38 },
	{ 0x00, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66 },
	{ 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x63, 0x77, 0x7F, 0x6B, 0x6B },
	{ 0x00, 0x00, 0x00, 0x7C, 0x7E, 0x66, 0x66, 0x66 },
	{ 0x00, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C },
	{ 0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60 },
	{ 0x00, 0x00, 0x3C, 0x6C, 0x6C, 0x3C, 0x0D, 0x0F },
	{ 0x00, 0x00, 0x00, 0x7C, 0x66, 0x66, 0x60, 0x60 },
	{ 0x00, 0x00, 0x00, 0x3E, 0x40, 0x3C, 0x02, 0x7C },
	{ 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E },
	{ 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x3C, 0x18 },
	{ 0x00, 0x00, 0x00, 0x63, 0x6B, 0x6B, 0x6B, 0x3E },
	{ 0x00, 0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66 },
	{ 0x00, 0x00, 0x00, 0x66, 0x66, 0x3E, 0x06, 0x3C },
	{ 0x00, 0x00, 0x00, 0x3C, 0x0C, 0x18, 0x30, 0x3C },
	{ 0x00, 0x0E, 0x18, 0x18, 0x30, 0x18, 0x18, 0x0E },
	{ 0x00, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18 },
	{ 0x00, 0x70, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x70 },
	{ 0x00, 0x00, 0x00, 0x3A, 0x6C, 0x00, 0x00, 0x00 },
};

#endif