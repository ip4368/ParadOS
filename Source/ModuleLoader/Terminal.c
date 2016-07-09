
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/Font.h"
#include "Library/String.h"
#include "ModuleLoader/Graphics.h"
#include <stdarg.h>

#define NUMBER_INDEX 16
#define UPPER_INDEX 33
#define LOWER_INDEX 65

#define LETTER_SIZE_X 14
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
	uint32 size = 0;
	uint32 arg_num = 0;
	char current;
	char next;
	va_list arg_list;
	va_start(arg_list, text);
	//Frist, we need to know how many args we have.
	while(text[size] != '\0') {
		//get current letter
		char current = text[size];
		char next = text[size + 1];
		if(current == '%'){
			if(next == 's' || next == 'd'){
				arg_num++;
				size++; //jump over 2 letter
			}
		}
		size++;
	}

	//Second, Print all the things.
	size = 0; //reset.
	while(text[size] != '\0'){ //another loop..
		current = text[size];
		next = text[size + 1];
		
		//check position
		if(cursorX >= cursorX_Max){ //if current row is at the end, then break.
			cursorX = 0;
			cursorY++;
			break;
		}		
		if(cursorY >= cursorY_Max){ //if the columns ran out, then clean screen. PS. we cant use runtime allocate service yet, so we wont do scrolling.
			CleanScreen();
			cursorX = 0;
			cursorY = 0;
			break;
		}

		switch(current){
			case ' ':{ //get a space
				cursorX++;
				break;
			}
			case '\n':{
				cursorY++;
				cursorX = 0;
				break;
			}
			case '%':{

				if(arg_num != 0){
					if(next == 'd'){
							char buffer[50];
							int temp = va_arg(arg_list, int);
							uint8 length = ToString(temp, buffer);
							for(int i = length; i >= 0; i--){
								PrintChar(buffer[i], color);
								cursorX++;
							}
							arg_num--;
					}else if(next == 's'){
						char *temp = va_arg(arg_list, char*);
						Print(temp);
						arg_num--;
					}
				}
				if(next == '%'){
				PrintChar(current, color);
				cursorX++;
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
