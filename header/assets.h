#pragma once

#define AMT_HINTS (3)

extern CP_Color BG_Grey, Red, Green, Black, Blue, White, Brown;
extern CP_Color Light_Sand, Dark_Sand, Water, Dark_Water, Grass, Dark_Grass, Slime_Wall, Slime_Wall_Outline;

extern CP_Font body_font, title_font;

extern CP_Image sch_logo, team_logo;
extern CP_Image MM_grass, MM_horse1, MM_horse2;
extern CP_Image MM_title;
extern CP_Image LVL_hint[AMT_HINTS];

extern CP_Sound MM_bg, UI_click, UI_win, UI_lose, UI_youLose;
extern CP_Sound horse_1, horse_2, horse_3, horse_4, horse_5;
extern CP_Sound GP_release, GP_slime, GP_wall, GP_sand;


//extern CP_Image horse_mc;

void set_assets(void);
void set_splash_assets(void);
void set_music_assets(void);
void FreeAsset();