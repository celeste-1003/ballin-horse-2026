#include "cprocessing.h"
#include "header/constants.h"
#include "header/mainmenu.h"
#include "header/credits.h"

CP_Image credits = NULL;
float scrollY;

void credits_init(void) {
	credits = CP_Image_Load("Assets/logos/credits.png");
	scrollY = (float)SCREEN_HEIGHT + SCREEN_HEIGHT / 2.0f;
}

void credits_update(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	scrollY -= CREDITS_SCROLL_SPEED * CP_System_GetDt();

	if (scrollY + SCREEN_HEIGHT / 2.0f < 0.0f || CP_Input_KeyTriggered(KEY_ESCAPE) || CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
		return;
	}
	
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(credits, SCREEN_WIDTH/2, scrollY, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 255);
}

void credits_exit(void) {
	CP_Image_Free(credits);
}