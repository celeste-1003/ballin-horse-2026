#include "cprocessing.h"
#include "header/assets.h"

CP_Color BG_Grey, Red, Green, Black, Blue, White;
CP_Color Light_Sand, Dark_Sand, Water, Dark_Water, Grass, Dark_Grass;
CP_Font body_font, title_font;
CP_Image sch_logo = NULL, team_logo = NULL;
//CP_Image horse_mc = NULL;

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

	// Colour
	Light_Sand = CP_Color_Create(232, 213, 145, 255);
	Dark_Sand = CP_Color_Create(220, 200, 130, 255);
	Water = CP_Color_Create(60, 120, 200, 255);
	Dark_Water = CP_Color_Create(75, 135, 215, 255);
	Grass = CP_Color_Create(60, 160, 70, 255);
	Dark_Grass = CP_Color_Create(72, 175, 82, 255);

	body_font = CP_Font_Load("Assets/fonts/ComicSans.ttf");
	title_font = CP_Font_Load("Assets/fonts/Kbpaythelady-WAyV.ttf");

	//horse_mc = CP_Image_Load("Assets/sprites/horse_golf_ball.png");
}

void set_splash_assets(void) {
	sch_logo = CP_Image_Load("Assets/logos/DigiPen_BLACK.png");
	team_logo = CP_Image_Load("Assets/logos/DigiPen_Singapore_WEB_RED.png");
}

void FreeAsset() {
	CP_Font_Free(body_font);
	CP_Font_Free(title_font);
}