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
int ToString(int64 input, char *buffer);
int ToString(uint64 input, char *buffer);

int ToHexString(int64 input, char *buff, bool upper);
uint64 TextToHex(char *buff);

char* strcpy(char *S1, const char *S2);
char* strncpy(char *S1, const char *S2, uint64 n);
#endif