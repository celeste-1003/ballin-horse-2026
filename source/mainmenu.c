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

// Confirmation Modal
static CP_BOOL show_exit_confirm = FALSE;
static Button btn_confirm_yes;
static Button btn_confirm_no;

/* MAIN FUNCTIONS */

// Initialize stuff
void main_menu_init(void)
{
	set_assets();
	set_music_assets();

	CP_Sound_PlayAdvanced(MM_bg, 0.5f, 1.0f, TRUE, CP_SOUND_GROUP_1);

	// Setup PLAY button
	btn_play.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2.0f);
	btn_play.button_y = PLAY_Y - (MMBUTTON_HEIGHT / 2.0f);
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
	btn_exit.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2.0f);
	btn_exit.button_y = EXIT_Y - (MMBUTTON_HEIGHT / 2.0f);
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
	btn_credits.button_x = BUTTON_X - (MMBUTTON_WIDTH / 2.0f);
	btn_credits.button_y = CREDITS_Y - (MMBUTTON_HEIGHT / 2.0f);
	btn_credits.width = MMBUTTON_WIDTH;
	btn_credits.height = MMBUTTON_HEIGHT;
	btn_credits.radius = 15.0f;
	btn_credits.label = "Credits";
	btn_credits.base = Brown;
	btn_credits.font = body_font;
	btn_credits.text_size = 50.0f;
	btn_credits.enabled = TRUE;
	btn_credits.press_anim = 0.0f;

	// Setup Confirmation Buttons
	show_exit_confirm = FALSE;
	const float modal_y = (float)SCREEN_HEIGHT / 2.0f;
	const float btn_w = 140.0f;
	const float btn_h = 55.0f;
	const float btn_gap = 40.0f;

	btn_confirm_yes = (Button){ 0 };
	btn_confirm_yes.width = btn_w;
	btn_confirm_yes.height = btn_h;
	btn_confirm_yes.button_x = (SCREEN_WIDTH / 2.0f) - btn_w - (btn_gap / 2.0f);
	btn_confirm_yes.button_y = modal_y + 40.0f;
	btn_confirm_yes.radius = 15.0f;
	btn_confirm_yes.label = "Yes";
	btn_confirm_yes.base = Red;
	btn_confirm_yes.font = body_font;
	btn_confirm_yes.text_size = 36.0f;
	btn_confirm_yes.enabled = TRUE;

	btn_confirm_no = (Button){ 0 };
	btn_confirm_no.width = btn_w;
	btn_confirm_no.height = btn_h;
	btn_confirm_no.button_x = (SCREEN_WIDTH / 2.0f) + (btn_gap / 2.0f);
	btn_confirm_no.button_y = modal_y + 40.0f;
	btn_confirm_no.radius = 15.0f;
	btn_confirm_no.label = "No";
	btn_confirm_no.base = Brown;
	btn_confirm_no.font = body_font;
	btn_confirm_no.text_size = 36.0f;
	btn_confirm_no.enabled = TRUE;
}

// Main
void main_menu_update(void)
{
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_ClearBackground(BG_Grey);

	CP_Image_Draw(MM_grass, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 255);

	/* ACTUAL TITLE PNG */
	CP_Image_Draw(MM_title, BUTTON_X, TITLE_Y, SCREEN_WIDTH, SCREEN_HEIGHT, 255);

	CP_Image_Draw(MM_horse1, 1300.0f, 625.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
	CP_Image_Draw(MM_horse2, 300.0f, 625.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255);

	UI_drawbutton(&btn_play);
	UI_drawbutton(&btn_exit);
	UI_drawbutton(&btn_credits);

	if (!show_exit_confirm) {
		if (UI_updatebutton(&btn_play)) {
			CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
		}

		if (UI_updatebutton(&btn_exit)) {
			show_exit_confirm = TRUE;
		}

		if (UI_updatebutton(&btn_credits)) {
			CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
		}
	}
	else {
		// Semi-transparent backdrop
		CP_Settings_Save();
		CP_Settings_NoStroke();
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 180));
		CP_Graphics_DrawRect(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
		CP_Settings_Restore();

		// Modal box
		const float modal_w = 600.0f;
		const float modal_h = 240.0f;
		const float modal_cx = (float)SCREEN_WIDTH / 2.0f;
		const float modal_cy = (float)SCREEN_HEIGHT / 2.0f;

		CP_Settings_Save();
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(CP_Color_Create(35, 35, 35, 255));
		CP_Settings_Stroke(CP_Color_Create(240, 240, 240, 255));
		CP_Settings_StrokeWeight(3.0f);
		CP_Graphics_DrawRect(modal_cx, modal_cy, modal_w, modal_h);

		CP_Settings_TextSize(36.0f);
		draw_text(title_font, White, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
			"Are you sure you want to leave?", modal_cx, modal_cy - 40.0f);
		CP_Settings_Restore();

		// Draw & Update modal buttons
		UI_drawbutton(&btn_confirm_yes);
		UI_drawbutton(&btn_confirm_no);

		if (UI_updatebutton(&btn_confirm_yes)) {
			CP_Engine_Terminate();
		}
		if (UI_updatebutton(&btn_confirm_no)) {
			show_exit_confirm = FALSE;
		}
	}
}

// Free up all stuff that was used
void main_menu_exit(void)
{
	show_exit_confirm = FALSE;
	//CP_Sound_Free(MM_bg);
}