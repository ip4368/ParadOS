
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/Font.h"
#include "Library/Operations.h"
#include "ModuleLoader/Video.h"

#define TERMINAL_DEFAULT_COLOR 0xFFFFFF

#define NUMBER_INDEX 16
#define UPPER_INDEX 33
#define LOWER_INDEX 65

uint64 cursorX;
uint64 cursorY;

void PrintChar(char letter, uint32 color);

void TerminalSetup()
{
	cursorX = 2;
	cursorY = 2;
}

void SetCursor(uint64 X, uint64 Y)
{
	if(IsVaildPosition(X, Y)) {
		cursorX = X;
		cursorY = Y;
	}
}


void Print(char *text)
{
	Print(text, TERMINAL_DEFAULT_COLOR);
}

void Print(const char *text, uint32 color)
{
	uint32 size = 0;
	while(text[size] != '\0') {
		char temp = text[size];
		if(temp == '\n' || !IsVaildPosition(0, cursorY)) {

			if(IsVaildPosition(0, cursorY + 16)) {
				cursorY += 16;
				cursorX = 2;
			} else {
				ClearScreen();
				SetCursor(2,2);
			}

		} else if(temp == ' ') {
			if(IsVaildPosition(cursorX + 8, 0)) {
				cursorX += 4;
			} else {
				cursorX = 2;
				cursorY += 16;
			}
		} else {
			PrintChar(text[size], color);
			cursorX += 16;
		}
		size++;
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
				DrawPixel(cursorX + TempX, cursorY + TempY, color);
				DrawPixel(cursorX + TempX + 1, cursorY + TempY, color);
				DrawPixel(cursorX + TempX, cursorY + TempY + 1, color);
				DrawPixel(cursorX + TempX + 1, cursorY + TempY + 1, color);
			}
			TempX += 2;
			TempData <<= 1;

		}
		TempY += 2;
	}


}
