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
int ToString(int8 input, char buffer[]);
int ToString(int16 input, char buffer[]);
int ToString(int32 input, char buffer[]);
int ToString(int64 input, char buffer[]);

int ToString(uint8 input, char buffer[]);
int ToString(uint16 input, char buffer[]);
int ToString(uint32 input, char buffer[]);
int ToString(uint64 input, char buffer[]);

int ToHexString(int64 input, char buff[]);
#endif