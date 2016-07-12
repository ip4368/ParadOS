
#include "Library/String.h"

uint64 strlen(char *in)
{
	uint64 result = 0;
	while(in[result] != '\0') {
		result++;
	}
	return result;
}

bool IsNumber(char input)
{
	int index = (int)input;
	if(index >= (int)'0' && index <= (int)'9') {
		return true;
	}
	return false;
}

bool IsLetter(char input)
{
	int index = (int)input;
	if((index >= (int)'A' && index <= (int)'Z') || (index >= (int)'a' && index <= (int)'z')) {
		return true;
	}
	return false;
}

bool IsUpperCase(char input)
{
	int index = (int)input;
	if(index >= (int)'A' && index <= (int)'Z') {
		return true;
	}
	return false;
}

bool IsLowerCase(char input)
{
	int index = (int)input;
	if(index >= (int)'a' && index <= (int)'z') {
		return true;
	}
	return false;
}

int ToString(int input, char buffer[]){
	int temp = input;
	int i = 0;
	if(input < 0){
		temp = -(temp);
	}
	do{
		buffer[i++] = temp % 10 + '0';
	}while((temp /= 10) > 0);

	if(input < 0){
		buffer[i++] = '-';
	}
	buffer[i] = '\0';
	return i;
}

int ToHexString(int input, char buffer[]){
	char ref[] = "0123456789ABCDEF";
	int temp = 0;
	int i = 0;

	while(input != 0){
		temp = input % 16;
		buffer[i++] = ref[temp];
		input /= 16;
	}
	return i;
}
/*
char ToChar(unsigned)
*/