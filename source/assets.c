#include "cprocessing.h"
#include "header/assets.h"

CP_Color BG_Grey, Red, Green, Black, Blue, White;
CP_Font body_font, title_font;
CP_Image sch_logo = NULL, team_logo = NULL;


/**
 @brief this initialises colors and fonts used in other systems
 @remarks no images, images will be loaded in 
 */
void set_assets(void) {
	static int loaded = 0;
	if (loaded) return;
	loaded = 1;
	
	BG_Grey = CP_Color_Create(128, 128, 128, 255);
	Red = CP_Color_Create(220, 20, 60, 255);
	Black = CP_Color_Create(0, 0, 0, 255);
	Blue = CP_Color_Create(100, 149, 237, 255);
	White = CP_Color_Create(255, 255, 255, 255);

	body_font = CP_Font_Load("Assets/fonts/ComicSans.ttf");
	title_font = CP_Font_Load("Assets/fonts/Kbpaythelady-WAyV.ttf");
}

void set_splash_assets(void) {
	sch_logo = CP_Image_Load("Assets/logos/DigiPen_BLACK.png");
	team_logo = CP_Image_Load("Assets/logos/DigiPen_Singapore_WEB_RED.png");
}