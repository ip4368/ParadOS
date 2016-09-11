
#include "Library/String.h"
#include "ModuleLoader/Terminal.h"
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

int ToString(int64 input, char *buffer){
	int64 temp = input;
	int i = 0;
	if(input < 0){
		temp = -(temp);
	}
	do{
		buffer[i++] = temp % 10 + '0';
	}while((temp /= 10) > 0);

	if(input < 0){
		buffer[i++] = '-';
	}else if(input < 10){
		buffer[i++] = '0';
	}
	return i;
}

int ToString(uint64 input, char *buffer){
	uint64 temp = input;
	int i = 0;
	do{
		buffer[i++] = temp % 10 + '0';
	}while((temp /= 10) > 0);

	if(input < 10){
		buffer[i++] = '0';
	}
	return i;
}

int ToHexString(int64 input, char *buffer, bool upper){
	char ref_up[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char ref_low[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	char *ref_ptr;
	int i = 0;
	
	if(upper){
		ref_ptr = ref_up;
	}else{
		ref_ptr = ref_low;
	}

	while(input >= 0){
		if(input < 16){
			buffer[i++] = ref_ptr[input];
			break;
		}
		buffer[i++] = ref_ptr[input%16];
		input /= 16;
	}

	return i;
}

uint64 TextToHex(char *buff){

}


/*		Memory copying 		*/

char* strcpy(char *S1, const char *S2){
	uint64 i = 0;
	while(S2[i] != '\0'){
		S1[i] = S2[i];
		i++;
	}
	return S1;
}

char* strncpy(char *S1, const char *S2, uint64 n){
	uint64 i = 0;
	while(i != n){
		S1[i] = S2[i];
		i++;
	}
	return S1;
}
