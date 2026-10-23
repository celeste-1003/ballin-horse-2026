/* MAIN MENU */
// Libraries
#include "header/mainmenu.h"
#include "cprocessing.h"
#include "header/utils.h"
#include "header/draw.h"
#include "header/lvlselect.h"
#include "header/constants.h"
#include "header/assets.h"

/* VARIABLES */
float textsize;
float click_x;
float click_y;

// Text
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
float text_x = 800.0f;

/* MAIN FUNCTIONS */
// Initialize stuff
void main_menu_init(void){
	set_assets();
	textsize = 70.0f;
	CP_Settings_TextSize(textsize);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

// Main
void main_menu_update(void){
	CP_Graphics_ClearBackground(BG_Grey);

	/* TITLE PLACEHOLDER */
	draw_rect(BUTTON_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, Red);
	draw_text(title_font, Black, horizontal, vertical, "Ballin' Horse", text_x, TITLE_Y);

	/* DRAW PLAY BUTTON */
	draw_rect(BUTTON_X, PLAY_Y, MMBUTTON_WIDTH, MMBUTTON_HEIGHT, Red);
	draw_text(body_font, Black, horizontal, vertical, "Play", text_x, PLAY_Y);
	
	// Change to game state when clicked
	if (CP_Input_MouseClicked()){
		if (IsAreaClicked(BUTTON_X, PLAY_Y, MMBUTTON_WIDTH, MMBUTTON_HEIGHT, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
	}

	/* DRAW EXIT BUTTON */
	draw_rect(BUTTON_X, EXIT_Y, MMBUTTON_WIDTH, MMBUTTON_HEIGHT, Red);
	draw_text(body_font, Black, horizontal, vertical, "Exit", text_x, EXIT_Y);
	
	// Exit Game
	if (CP_Input_MouseClicked()){
		if (IsAreaClicked(BUTTON_X, EXIT_Y, MMBUTTON_WIDTH, MMBUTTON_HEIGHT, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			CP_Engine_Terminate();
	}
}

// Free up all stuff that was used
void main_menu_exit(void){
	CP_Font_Free(body_font);
	CP_Font_Free(title_font);
}