/* LEVEL SELECT */
//Libraries
#include "cprocessing.h"
#include "header/draw.h"
#include "header/constants.h"
#include "header/assets.h"
#include <stdbool.h>
#include "header/game.h"
#include "header/mainmenu.h"
#include "header/ui.h"

Button lvl_buttons[AMT_LVL_BOXES];
static char level_labels[AMT_LVL_BOXES][16];

void lvlselect_init(void) {
    set_assets();
    CP_Settings_RectMode(CP_POSITION_CENTER);

    float total_grp_width = (AMT_LVL_BOXES * LVL_WIDTH) + ((AMT_LVL_BOXES - 1) * GAP_SPACE);
    float start_x = (SCREEN_WIDTH / 2.0f) - (total_grp_width / 2.0f) + (LVL_WIDTH / 2.0f);

    for (int i = 0; i < AMT_LVL_BOXES; i++) {
        float center_x = start_x + (i * (LVL_WIDTH + GAP_SPACE));
        float center_y = SCREEN_HEIGHT / 2.0f;

        lvl_buttons[i].button_x = center_x - (LVL_WIDTH / 2.0f);
        lvl_buttons[i].button_y = center_y - (LVL_HEIGHT / 2.0f);
        lvl_buttons[i].width = LVL_WIDTH;
        lvl_buttons[i].height = LVL_HEIGHT;
        lvl_buttons[i].radius = 15.0f;

        sprintf_s(level_labels[i], 16, "Level %d", i + 1);
        lvl_buttons[i].label = level_labels[i];

        lvl_buttons[i].base = Red;
        lvl_buttons[i].font = body_font;
        lvl_buttons[i].text_size = 30.0f;
        lvl_buttons[i].enabled = TRUE;
        lvl_buttons[i].press_anim = 0.0f;
    }
}

void lvlselect_update(void) {
    CP_Graphics_ClearBackground(BG_Grey);

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
    }

    for (int i = 0; i < AMT_LVL_BOXES; i++) {
        UI_drawbutton(&lvl_buttons[i]);

        if (UI_updatebutton(&lvl_buttons[i])) {
            // for future use
            // g_selectedLevel = i + 1; 

            CP_Engine_SetNextGameState(game_init, game_update, game_exit);
        }
    }
}

void lvlselect_exit(void) {

}