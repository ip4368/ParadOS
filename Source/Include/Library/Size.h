#ifndef _LIBRARY_SIZE_H_
#define _LIBRARY_SIZE_H_
#include "Types.h"
#include "Library/Math.h"

typedef uint64 Size;

#define SIZE_BASE_KB 1024
#define SIZE_BASE_MB pow(1024, 2)
#define SIZE_BASE_GB pow(1024, 3)
#define SIZE_BASE_TB pow(1024, 4)

//Size should be in byte.
uint64 SizeConvert(uint64 Size, uint64 Base);
#endif