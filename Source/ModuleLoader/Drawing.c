#include "ModuleLoader/Drawing.h"

//the picture is potting from left to right, up to down.
uint32 DrawPicture(uint32 *picture, uint32 x, uint32 y, uint32 width, uint32 height){
	uint32 i = 0;

	for(uint32 h = 0; h < height; h++){//performace..and ugly logic..
		if(!IsVaildPosition(0, h + y)){
			break;
		}

		for(uint32 w = 0; w < width; w++){
			if(!IsVaildPosition(w + x, 0)){
				break;
			}
			uint32 color = picture[i];
			DrawPixel(w + x, h + y, color);
			i++;
		}
	}
	return i;
}

//return start position that make the middle of the picture is equal [pos]
uint32 CalculateStartPoint(uint32 pos, uint32 length){ 
	return (pos - (length / 2));
}
