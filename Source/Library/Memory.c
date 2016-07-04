#include "Library/Memory.h"

int memcopy(char* from, char* to, uint64 bytestocopy){
	uint64 i = 0;
	while(i != bytestocopy){
		*to[i] = *from;
		i++
	}
	return i;
}