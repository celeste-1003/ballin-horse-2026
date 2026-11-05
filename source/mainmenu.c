/* MAIN MENU */
// Libraries
#include "header/mainmenu.h"
#include "cprocessing.h"
#include "header/utils.h"
#include "header/draw.h"
#include "header/lvlselect.h"
#include "header/credits.h"
#include "header/constants.h"
#include "header/assets.h"
#include "header/ui.h"

/* VARIABLES */
//float textsize;
float click_x;
float click_y;

// Text
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
float text_x = 800.0f;

Button btn_play;
Button btn_exit;
Button btn_credits;

/* MAIN FUNCTIONS */
// Initialize stuff
void main_menu_init(void){
	set_assets();

	// Setup PLAY button
	btn_play.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2); 
	btn_play.button_y = PLAY_Y - (MMBUTTON_HEIGHT / 2);
	btn_play.width = MMBUTTON_WIDTH;
	btn_play.height = MMBUTTON_HEIGHT;
	btn_play.radius = 15.0f;
	btn_play.label = "Play";
	btn_play.base = Brown;
	btn_play.font = body_font;      
	btn_play.text_size = 50.0f;       
	btn_play.enabled = TRUE;
	btn_play.press_anim = 0.0f;

	// Setup EXIT button
	btn_exit.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2);
	btn_exit.button_y = EXIT_Y - (MMBUTTON_HEIGHT / 2);
	btn_exit.width = MMBUTTON_WIDTH;
	btn_exit.height = MMBUTTON_HEIGHT;
	btn_exit.radius = 15.0f;
	btn_exit.label = "Exit";
	btn_exit.base = Brown;
	btn_exit.font = body_font;       
	btn_exit.text_size = 50.0f;
	btn_exit.enabled = TRUE;
	btn_exit.press_anim = 0.0f;

	// Setup CREDIT button
	btn_credits.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2);
	btn_credits.button_y = CREDITS_Y - (MMBUTTON_HEIGHT / 2);
	btn_credits.width = MMBUTTON_WIDTH;
	btn_credits.height = MMBUTTON_HEIGHT;
	btn_credits.radius = 15.0f;
	btn_credits.label = "Credits";
	btn_credits.base = Brown;
	btn_credits.font = body_font;
	btn_credits.text_size = 50.0f;
	btn_credits.enabled = TRUE;
	btn_credits.press_anim = 0.0f;
}

// Main
void main_menu_update(void){
	
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(BG_Grey);

	CP_Image_Draw(MM_grass, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
	
	/* TITLE PLACEHOLDER */
	//draw_rect(BUTTON_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, Red);
	//CP_Settings_TextSize(TITLE_TEXTSIZE);
	//draw_text(title_font, White, horizontal, vertical, "Ballin' Horse!!", text_x, TITLE_Y);
	
	/* ACTUAL TITLE PNG */
	CP_Image_Draw(MM_title, BUTTON_X, TITLE_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 255);


	CP_Image_Draw(MM_horse1, 1300.0f, 625.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255);

	UI_drawbutton(&btn_play);
	if (UI_updatebutton(&btn_play)) {
		CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
	}

	UI_drawbutton(&btn_exit);
	if (UI_updatebutton(&btn_exit)) {
		CP_Engine_Terminate();
	}

	UI_drawbutton(&btn_credits);
	if (UI_updatebutton(&btn_credits)) {
		CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
	}

	CP_Image_Draw(MM_horse2, 300.0f, 625.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
}

// Free up all stuff that was used
void main_menu_exit(void){

}