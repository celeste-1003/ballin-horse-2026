#include "cprocessing.h"
#include "header/assets.h"

CP_Color BG_Grey, Red, Green, Black, Blue, White, Brown;
CP_Color Light_Sand, Dark_Sand, Water, Dark_Water, Grass, Dark_Grass, Slime_Wall, Slime_Wall_Outline;

CP_Font body_font, title_font;

CP_Image sch_logo = NULL, team_logo = NULL;
CP_Image MM_grass = NULL, MM_horse1 = NULL, MM_horse2 = NULL;
CP_Image MM_title = NULL;
CP_Image LVL_hint[AMT_HINTS] = { NULL }, flag_sheet = NULL;

CP_Sound MM_bg = NULL, UI_click = NULL, UI_win = NULL, UI_lose = NULL, UI_youLose = NULL;
CP_Sound horse_1 = NULL, horse_2 = NULL, horse_3 = NULL, horse_4 = NULL, horse_5 = NULL;
CP_Sound GP_release = NULL, GP_slime = NULL, GP_wall = NULL, GP_sand = NULL;


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
	Brown = CP_Color_Create(181, 96, 2, 225);

	// colour of blocks n stuff
	Light_Sand = CP_Color_Create(232, 213, 145, 255);
	Dark_Sand = CP_Color_Create(220, 200, 130, 255);
	Water = CP_Color_Create(60, 120, 200, 255);
	Dark_Water = CP_Color_Create(75, 135, 215, 255);
	Grass = CP_Color_Create(60, 160, 70, 255);
	Dark_Grass = CP_Color_Create(72, 175, 82, 255);

	Slime_Wall = CP_Color_Create(171, 240, 126, 255);
	Slime_Wall_Outline = CP_Color_Create(150, 222, 101, 200);

	//fonts
	body_font = CP_Font_Load("Assets/fonts/ComicSans.ttf");
	title_font = CP_Font_Load("Assets/fonts/Kbpaythelady-WAyV.ttf");

	//horse_mc = CP_Image_Load("Assets/sprites/horse_golf_ball.png");
	MM_grass = CP_Image_Load("./Assets/sprites/homepage_bg.png");
	MM_horse1 = CP_Image_Load("./Assets/sprites/homepage_horse1.png");
	MM_horse2 = CP_Image_Load("./Assets/sprites/homepage_horse2.png");

	//title
	MM_title = CP_Image_Load("Assets/sprites/TITLE.png");

	//hints
	LVL_hint[0] = CP_Image_Load("Assets/sprites/LVL1HINT.png");
	LVL_hint[1] = CP_Image_Load("Assets/sprites/LVL2HINT.png");
	LVL_hint[2] = CP_Image_Load("Assets/sprites/LVL3HINT.png");

	//goal hole
	flag_sheet = CP_Image_Load("Assets/sprites/FLAGSHEET1.png");
}

void set_music_assets(void) {

	MM_bg = CP_Sound_LoadMusic("Assets/music/mm_bgmusic.mp3");
	UI_click = CP_Sound_Load("Assets/music/ui_click.wav");
	UI_win = CP_Sound_LoadMusic("Assets/music/ui_win.wav");
	UI_lose = CP_Sound_LoadMusic("Assets/music/ui_lose.wav");
	UI_youLose = CP_Sound_Load("Assets/music/ui_youLose.wav");

	horse_1 = CP_Sound_Load("Assets/music/ui_horse1.wav");
	horse_2 = CP_Sound_Load("Assets/music/ui_horse2.wav");
	horse_3 = CP_Sound_Load("Assets/music/ui_horse3.wav");
	horse_4 = CP_Sound_Load("Assets/music/ui_horse4.wav");
	horse_5 = CP_Sound_Load("Assets/music/ui_horse5.wav");

	GP_release = CP_Sound_Load("Assets/music/gp_release.wav");
	GP_slime = CP_Sound_Load("Assets/music/gp_slime.flac");
	GP_wall = CP_Sound_Load("Assets/music/gp_wall.wav");
	GP_sand = CP_Sound_Load("Assets/music/gp_sand.wav");
}

void set_splash_assets(void) {
	sch_logo = CP_Image_Load("Assets/logos/DigiPen_BLACK.png");
	team_logo = CP_Image_Load("Assets/logos/DigiPen_Singapore_WEB_RED.png");
}

void FreeAsset() {
	CP_Font_Free(body_font);
	CP_Font_Free(title_font);
}