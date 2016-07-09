#include "ModuleLoader/Panic.h"

void Panic(char* msg, uint8 level)
{
	//never get level 1 error
	if(level == PANIC_LEVEL_TWO){
		SetColor(0xFF0000);
		Print(msg);
		
	}else if(level == PANIC_LEVEL_THREE){
		SetColor(0xFFFF00);
		Print(msg);
		
	}else if(level == PANIC_LEVEL_FOUR){
		SetColor(0xADFF2F);
		Print(msg);
		
	}
	
}