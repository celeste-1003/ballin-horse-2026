#include "cprocessing.h"

CP_Font myFont;

void init() 
	{
		myFont = CP_Font_Load("arial.ttf", 20);
	}

void test(void)
{
	
	CP_Font_Set(myFont);

	CP_Font_DrawText("Hello World!", CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2);
}
