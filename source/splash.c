// splash.c

#include "header/splash.h"
#include "cprocessing.h"
#include "header/constants.h"
#include "header/assets.h"
#include "header/mainmenu.h"

static CP_Image logos[SPLASH_COUNT];
static int current;
static float timer;

static CP_BOOL splash_skip_pressed(void) {
	return CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT);
}

void splash_init(void) {
	CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	set_splash_assets();

	logos[0] = sch_logo;
	logos[1] = team_logo;

	current = 0;
	timer = 0.0f;
}

void splash_update(void) {
	timer += CP_Math_ClampFloat(CP_System_GetDt(), 0.0f, 1.0f / 30.0f);
	if (splash_skip_pressed() || timer >= SPLASH_HOLD_TIME) {
		current++;
		timer = 0.0f;
		if (current >= SPLASH_COUNT) {
			CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
			return;
		}
	}

	float a = 1.0f;
	if (timer < SPLASH_FADE_TIME) {
		a = timer / SPLASH_FADE_TIME;
	}
	else if (timer > SPLASH_HOLD_TIME - SPLASH_FADE_TIME) {
		a = (SPLASH_HOLD_TIME - timer) / SPLASH_FADE_TIME;
	}
	a = CP_Math_ClampFloat(a, 0.0f, 1.0f);

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float width = (float)CP_Image_GetWidth(logos[current]);
	float height = (float)CP_Image_GetHeight(logos[current]);

	float scale;
	if ((SPLASH_MAX_W / width) < (SPLASH_MAX_H / height)) {
		scale = SPLASH_MAX_W / width;
	}
	else {
		scale = SPLASH_MAX_H / height;
	}

	CP_Image_Draw(logos[current], SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, width * scale, height * scale, (int)(a * 255.0f));
}

void splash_exit(void) {
	for (int i = 0; i < SPLASH_COUNT; i++) {
		CP_Image_Free(logos[i]);
	}

	sch_logo = NULL;
	team_logo = NULL;
}