/* MAIN MENU */
// Libraries
#include "mainmenu.h"
#include "cprocessing.h"
#include "game.h"
#include <stdio.h>
#include "utils.h"

/* VARIABLES */
CP_Color BG_Grey, Red, Green, Black, Blue, White;

float textsize;
float click_x;
float click_y;

// Button values
float button_x = 800.0f; // to start from the middle
float play_y = 600.0f;
float exit_y = 775.0f;
float area_width = 250.0f; // only for buttons
float area_height = 125.0f;
float title_width = 750.0f; // placeholder(?) for image
float title_height = 400.0f;
float title_y = 275.0f;

// Text
CP_Font myFont;
CP_Font titleFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
float text_x = 800.0f;

/* OTHER FUNCTIONS */
// Functions to draw rectangles
void draw_rect(float x, float y, float width, float height, CP_Color col) {
	CP_Settings_Fill(col);
	CP_Graphics_DrawRect(x, y, width, height);
}

// Functions to draw text
void draw_text(CP_Font font, CP_Color col, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v, 
	const char* text, float txt_x, float txt_y) {
	CP_Font_Set(font);
	CP_Settings_Fill(col);
	CP_Settings_TextAlignment(h, v);
	CP_Font_DrawText(text, txt_x, txt_y);

}

/* MAIN FUNCTIONS */
// Initialize stuff
void Main_Menu_Init(void)
{
	BG_Grey = CP_Color_Create(128, 128, 128, 255);
	Red = CP_Color_Create(220, 20, 60, 255);
	Black = CP_Color_Create(0, 0, 0, 255);
	Blue = CP_Color_Create(100, 149, 237, 255);
	White = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(BG_Grey);
	myFont = CP_Font_Load("../Assets/fonts/ComicSans.ttf");
	titleFont = CP_Font_Load("../Assets/fonts/Kbpaythelady-WAyV.ttf");
	textsize = 70.0f;
	CP_Settings_TextSize(textsize);
	CP_Settings_RectMode(CP_POSITION_CENTER);

}

// Main
void Main_Menu_Update(void)
{
	/* TITLE PLACEHOLDER */
	draw_rect(button_x, title_y, title_width, title_height, Red);
	draw_text(titleFont, Black, horizontal, vertical, "Ballin' Horse", text_x, title_y);

	/*!
	DRAW PLAY BUTTON
	//---------------*/
	draw_rect(button_x, play_y, area_width, area_height, Red);
	draw_text(myFont, Black, horizontal, vertical, "Play", text_x, play_y);
	
	// Change to game state when clicked
	if (CP_Input_MouseClicked()){
		if (IsAreaClicked(button_x, play_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);			
	}

	/*!
	DRAW EXIT BUTTON
	//---------------*/
	draw_rect(button_x, exit_y, area_width, area_height, Red);
	draw_text(myFont, Black, horizontal, vertical, "Exit", text_x, exit_y);
	
	// Exit Game
	if (CP_Input_MouseClicked()){
		if (IsAreaClicked(button_x, exit_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			CP_Engine_Terminate();
	}

}


// Free up all stuff that was used
void Main_Menu_Exit(void)
{
	CP_Font_Free(myFont);
}