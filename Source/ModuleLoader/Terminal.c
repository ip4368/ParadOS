
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/Font.h"
#include "Library/String.h"
#include "ModuleLoader/Graphics.h"
#include <stdarg.h>

#define TERMINAL_DEFAULT_COLOR 0xFFFFFF

#define NUMBER_INDEX 16
#define UPPER_INDEX 33
#define LOWER_INDEX 65

#define LETTER_SIZE_X 16 
#define LETTER_SIZE_Y 16

uint32 cursorX;
uint32 cursorY;

uint32 color = TERMINAL_DEFAULT_COLOR;

uint32 cursorY_Max = 0;
uint32 cursorX_Max = 0;
void PrintChar(char letter, uint32 color);

void TerminalSetup()
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
	uint64 size = 0;
	va_list arg_list;

	while(text[size] != '\0') {
		char temp = text[size];
		if(temp == '\n' || !IsVaildPosition(0, cursorY)) {

			if(IsVaildPosition(0, cursorY)) {
				cursorY++;
				cursorX = 0;
			} else {
				CleanScreen();
				SetCursor(0,0);
			}

		} else if(temp == ' ') {
			if(IsVaildPosition(cursorX + 1, 0)) {
				cursorX++;
			} else {
				cursorX = 0;
				cursorY++;
			}
		} else if(temp == '%'){
			char nextChar = text[size + 1];
			va_start(arg_list, text);
			switch(nextChar){
				case 'd':{//int
					char buffer[20];
					int  subint = va_arg(arg_list, int);
					int size = ToString(subint, buffer);
					for(int i = size; i >= 0; i--){
						PrintChar(buffer[i], color);
						cursorX++;
					}
					break;
				}
				case 's':{//string
					char *subString = va_arg(arg_list, char*);
					uint64 subStringSize = 0;
					while(subString[subStringSize] != '\0'){
						temp = subString[subStringSize];
						if(temp == '\n' || !IsVaildPosition(0, cursorY)) {

							if(IsVaildPosition(0, cursorY)) {
								cursorY++;
								cursorX = 0;
							} else {
								CleanScreen();
								SetCursor(0,0);
							}
						}else if(temp == ' ') {
								if(IsVaildPosition(cursorX + 1, 0)) {
									cursorX++;
								} else {
									cursorX = 0;
									cursorY++;
								}
							}else{
								PrintChar(temp, color);
								cursorX++;
							}
							subStringSize++;
						}
					va_end(arg_list);
					break;
				}
				default:{
					PrintChar('%', color);
					cursorX++;
					break;
				}
			}
			size++;
		}else {
			PrintChar(temp, color);
			cursorX++;
		}
		size++;
	}
	color = TERMINAL_DEFAULT_COLOR;
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
			index = 14;
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
				DrawPixel(cursorX * LETTER_SIZE_X + TempX, cursorY * LETTER_SIZE_Y + TempY, color);
				DrawPixel(cursorX * LETTER_SIZE_X + TempX + 1, cursorY * LETTER_SIZE_Y + TempY, color);
				DrawPixel(cursorX * LETTER_SIZE_X + TempX, cursorY * LETTER_SIZE_Y + TempY + 1, color);
				DrawPixel(cursorX * LETTER_SIZE_X + TempX + 1, cursorY * LETTER_SIZE_Y + TempY +1, color);
			}
			TempX += 2;
			TempData <<= 1; //shift to the left

		}
		TempY += 2;
	}


}
