
#include "ModuleLoader/Terminal.h"
#include "ModuleLoader/Font.h"

Terminal term;

void Terminal::Setup(Video vi)
{
	video = vi;
	cursorX = 2;
	cursorY = 2;
}

void Terminal::SetXY(uint64 X, uint64 Y)
{
	if(video.IsVaildRange(X, Y)) {
		cursorX = X;
		cursorY = Y;
	}
}


void Terminal::Print(char *text)
{
	Print(text, TERMINAL_DEFAULT_COLOR);
}
void Terminal::Print(const char *text, uint32 color)
{
	uint32 size = 0;
	while(text[size] != '\0') {
		char temp = text[size];
		if(temp == '\n' || !video.IsVaildRange(0, cursorY)) {

			if(video.IsVaildRange(0, cursorY + 10)) {
				cursorY += 10;
				cursorX = 2;
			} else {
				video.Clear();
				SetXY(2,2);
			}

		} else if(temp == ' ') {
			if(video.IsVaildRange(cursorX + 4, 0)) {
				cursorX += 4;
			} else {
				cursorX = 2;
				cursorY += 10;
			}
		} else {
			PrintChar(text[size], color);
			cursorX += 9;
		}
		size++;
	}
}

void Terminal::PrintChar(char letter, uint32 color)
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
		for(int row = 0; row <= 8; row++) {

			if(TempData >= 128) { //2^8
				video.DrawPixel(cursorX + TempX, cursorY + TempY, color);
			}
			TempX++;
			TempData <<= 1;

		}
		TempY++;
	}


}
