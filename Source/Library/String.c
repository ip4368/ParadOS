
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

int ToHexString(int input, char buff[]){

	char ref[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	int temp = 0;
	int i = 0;
	int q = input;
	do{
		temp = q % 16;
		buff[i++] = ref[temp];
	}while((q /= 16) > 0);
	buff[i] = '\0';
	return i;
}
/*
char ToChar(unsigned)
*/