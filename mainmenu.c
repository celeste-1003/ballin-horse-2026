// Libraries
#include "mainmenu.h"
#include "cprocessing.h"
#include "game.h"
#include <stdio.h>
#include "utils.h"

// Global variables
CP_Color BG_Grey, Red, Green, Black, Blue, White;

float textsize;
float click_x;
float click_y;

// Button values
float button_x = 800.0f;
float play_y = 250.0f;
float exit_y = 600.0f;
float area_width = 500;
float area_height = 250;

// Text
CP_Font myFont;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;


// Initialize stuff
void Main_Menu_Init(void)
{
	BG_Grey = CP_Color_Create(128, 128, 128, 255);
	Red = CP_Color_Create(220, 20, 60, 255);
	Black = CP_Color_Create(0, 0, 0, 255);
	Blue = CP_Color_Create(100, 149, 237, 255);
	White = CP_Color_Create(255, 255, 255, 255);
	CP_Graphics_ClearBackground(BG_Grey);
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	textsize = 70.0f;
	CP_Settings_TextSize(textsize);
	CP_Settings_RectMode(CP_POSITION_CENTER);

}

// Main
void Main_Menu_Update(void)
{
	/*!
	PLAY BUTTON
	//---------------*/
	CP_Settings_Fill(Red);
	CP_Font_Set(myFont);
	CP_Graphics_DrawRect(button_x, play_y, area_width, area_height); 
	CP_Settings_Fill(Black);
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Play", 800, 250);
	
	// Change to game state when clicked
	if (CP_Input_MouseClicked())
	{
		if (IsAreaClicked(button_x, play_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);			
	}

	/*!
	EXIT BUTTON
	//---------------*/
	CP_Settings_Fill(Red);
	CP_Font_Set(myFont);
	CP_Graphics_DrawRect(button_x, exit_y, area_width, area_height);
	CP_Settings_Fill(Black);
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Font_DrawText("Exit", 800, 600);
	
	// Exit Game
	if (CP_Input_MouseClicked())
	{
		if (IsAreaClicked(button_x, exit_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			CP_Engine_Terminate();
	}

}


// Free up all stuff that was used
void Main_Menu_Exit(void)
{
	CP_Font_Free(myFont);
}