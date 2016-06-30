#include "ModuleLoader/Panic.h"

void Panic(char* msg, uint8 level)
{
	//never get level 1 error
	if(level == PANIC_LEVEL_TWO){
		Print(msg, 0xFF0000);
		
	}else if(level == PANIC_LEVEL_THREE){
		Print(msg, 0xFFFF00);
		
	}else if(level == PANIC_LEVEL_FOUR){
		Print(msg, 0xADFF2F);
		
	}
	
}