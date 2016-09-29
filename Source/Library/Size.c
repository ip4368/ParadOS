#include "Library/Size.h"
#include "Library/String.h"

/*
	I dont know did the float work, or maybe i will fix it in the furture.
*/

uint64 SizeConvert(uint64 Size, uint64 Base){
	uint64 temp = Size / Base;
	return temp;
}