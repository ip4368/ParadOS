#ifndef _LIBRARY_STRING_H_
#define _LIBRARY_STRING_H_

#include "Types.h"

uint64 strlen(char *in);
bool IsLetter(char input);
bool IsNumber(char input);
bool IsUpperCase(char input);
bool IsLowerCase(char input);
/*
	Convert Operations
*/
int ToString(int input, char buffer[]);
int ToHexString(int input, char buff[]);
#endif