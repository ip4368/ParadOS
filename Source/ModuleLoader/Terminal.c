
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/Font.h"
#include "Library/String.h"
#include "ModuleLoader/Graphics.h"
#include <stdarg.h>

#define NUMBER_INDEX 16
#define UPPER_INDEX 33
#define LOWER_INDEX 65

#define PPD 1 //Pixel per dot

#define LETTER_SIZE_X (PPD * 8) - 1
#define LETTER_SIZE_Y PPD * 8

uint32 cursorX;
uint32 cursorY;

uint32 color = TERMINAL_DEFAULT_COLOR;

uint32 cursorY_Max = 0;
uint32 cursorX_Max = 0;
void PrintChar(char letter, uint32 color);

void SetupTerminal()
{
	cursorX = 0;
	cursorY = 0;

	if(GetHResolution() % LETTER_SIZE_X){//if resolution is odd number than reserve 1 word of the end of X
		cursorX_Max =  (GetHResolution() / LETTER_SIZE_X) - 1;
	}else{
		cursorX_Max =  (GetHResolution() / LETTER_SIZE_X);
	} 

	if(GetVResolution() % LETTER_SIZE_Y){//if resolution is odd number than reserve 1 word of the end of Y
		cursorY_Max =  (GetVResolution() / LETTER_SIZE_Y) - 1;
	}else{
		cursorY_Max =  (GetVResolution() / LETTER_SIZE_Y);
	} 

}

void SetCursor(uint32 X, uint32 Y)
{
	if((X > 0 && X <= cursorX_Max) && (Y > 0 && Y <= cursorY_Max)) {
		cursorX = X;
		cursorY = Y;
	}
}

void SetColor(uint32 c){ 
	color = c;
}

//dumbest method
void Print(const char *text, ...)
{
	uint32 size = 0;
	char current;
	va_list arg_list;
	va_start(arg_list, text);

	//simple method
	size = 0; //reset.
	while(text[size] != 0){ 
		current = text[size];
		
		//check position
		if(cursorX >= cursorX_Max){ //if current row is at the end, then break.
			cursorX = 0;
			cursorY++;
		}		
		if(cursorY >= cursorY_Max){ //if the columns ran out, then clean screen. PS. we cant use runtime allocate service yet, so we wont do scrolling.
			CleanScreen();
			cursorX = 0;
			cursorY = 0;
		}

		switch(current){
			case ' ':{ //got a space
				cursorX++;
				break;
			}
			case '\n':{ //next line
				cursorY++;
				cursorX = 0;
				break;
			}
			case '%':{
				char buffer[50];
				int length;

					switch(text[size + 1]){

						case '@':{ //runtime color change
							uint32 c_temp = (uint32)va_arg(arg_list, int);
							if(c_temp <= 0xffffff){
								SetColor(c_temp);
							}
							break;
						}
						/*
						case '#':{ //hard code color change
							char buffer[6];
							//copy 6 char to buffer
							strncpy(buffer, text[size + 2], 6);
							//parse buffer
							uint32 value = TextToHex(buffer);
							//check vaild 


							break;
						}

						*/
						case 'c':{ //char
							char b = (char)va_arg(arg_list, int);
							PrintChar(b, color);
							cursorX++;
							break;
						}

						case 'i':
						case 'd':{ //integer
							int64 d = (int64)va_arg(arg_list, int);
							length = ToString(d, buffer);
							
							for(int i = length - 1; i >= 0; i--){
								PrintChar(buffer[i], color);
								cursorX++;
							}
							break;
						}

						case 'u':{ //unsigned integer
							uint64 u = (uint64)va_arg(arg_list, int);
							length = ToString(u, buffer);
							
							for(int i = length - 1; i >= 0; i--){
								PrintChar(buffer[i], color);
								cursorX++;
							}
							break;
						}

						case 'X':{ //upper case hex
							uint64 temp;
							temp = va_arg(arg_list, uint64);
							length = ToHexString(temp, buffer, true);
							for(int i = length - 1;i >= 0; i--){
								PrintChar(buffer[i], color);
								cursorX++;
							}
							break;
						}

						case 'x':{ //lower case hex
							uint64 temp;
							temp = va_arg(arg_list, uint64);
							length = ToHexString(temp, buffer, false);
							for(int i = length - 1;i >= 0; i--){
								PrintChar(buffer[i], color);
								cursorX++;
							}	
							break;
						}

						case 's':{ //string
						char *tempString = va_arg(arg_list, char*);
						uint64 i = 0;
						while(tempString[i] != '\0'){
						PrintChar(tempString[i], color);
						cursorX++;
						i++;
						}
						break;
						}

						case '%':{ //just a '%'
							PrintChar(current, color);
							cursorX++;
							break;
						}
						default:{
							break;
						}
					}
				size++;
				break;
			}
			default:{
				PrintChar(current, color);
				cursorX++;
				break;
			}
		}
		size++; //next.
	}
	color = TERMINAL_DEFAULT_COLOR;
	va_end(arg_list);
}
		
void PrintChar(char letter, uint32 color)
{
	int index = 0;
	int TempX = 0;
	int TempY = 0;
	uint8 *TempArray;
	if(IsLetter(letter)) {
		if(IsUpperCase(letter)) {
			index = (int)letter - (int)'A' + UPPER_INDEX;
		} else {
			index = ((int)letter - (int)'a') + LOWER_INDEX;
		}

	} else if(IsNumber(letter)) {
		index = ((int)letter - (int)'0') + NUMBER_INDEX;
	} else {
		switch(letter) {
		case '!':
			index = 1;
			break;

		case '"':
			index = 2;
			break;

		case '#':
			index = 3;
			break;

		case '$':
			index = 4;
			break;

		case '%':
			index = 5;
			break;

		case '&':
			index = 6;
			break;

		case '\'':
			index = 7;
			break;

		case ')':
			index = 8;
			break;

		case '(':
			index = 9;
			break;

		case '*':
			index = 10;
			break;

		case '+':
			index = 11;
			break;

		case ',':
			index = 12;
			break;

		case '-':
			index = 13;
			break;

		case '.':
			index = 14;
			break;

		case '/':
			index = 15;
			break;

		case ':':
			index = 26;
			break;

		case ';':
			index = 27;
			break;

		case '<':
			index = 28;
			break;

		case '=':
			index = 29;
			break;

		case '>':
			index = 30;
			break;

		case '?':
			index = 31;
			break;

		case '@':
			index = 32;
			break;

		case '[':
			index = 59;
			break;

		case '\\':
			index = 60;
			break;

		case ']':
			index = 61;
			break;

		case '^':
			index = 62;
			break;

		case '_':
			index = 63;
			break;

		case '`':
			index = 64;
			break;

		case '{':
			index = 91;
			break;

		case '|':
			index = 92;
			break;

		case '}':
			index = 93;
			break;

		case '~':
			index = 94;
			break;

		default:
			index = 0;


		}
	}

	TempArray = Font_Data[index];

	for(int col = 0; col <= 7; col++) {
		TempX = 0;
		uint8 TempData = TempArray[col];
		for(int row = 0; row <= 7; row++) {

			if(TempData >= 128) { //2^8
					
					for(uint8 y = 0; y < PPD; y++){
						for(uint8 x = 0; x < PPD; x++){
							DrawPixel(cursorX * LETTER_SIZE_X + TempX + x, cursorY * LETTER_SIZE_Y + TempY + y, color);
						}
					}
			}
			TempX += PPD;
			TempData <<= 1; //shift to the left

		}
		TempY+= PPD;
	}


}
