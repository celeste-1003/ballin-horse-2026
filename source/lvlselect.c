/* LEVEL SELECT */
//Libraries
#include "cprocessing.h"
#include "header/draw.h"
#include "header/constants.h"
#include "header/assets.h"
#include <stdbool.h>
#include "header/game.h"
#include "header/mainmenu.h"

//CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
//CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;

void lvlselect_init(void) {
    set_assets();
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

void lvlselect_update(void) {
    CP_Graphics_ClearBackground(BG_Grey);

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_SetNextGameState(main_menu_update, main_menu_update, main_menu_exit);
    }

    float mouse_x = CP_Input_GetMouseX();
    float mouse_y = CP_Input_GetMouseY();
    bool clicked = CP_Input_MouseClicked();

    float total_grp_width = (AMT_LVL_BOXES * LVL_WIDTH) + ((AMT_LVL_BOXES - 1) * GAP_SPACE);
    float start_x = (1600.0f / 2.0f) - (total_grp_width / 2.0f) + (LVL_WIDTH / 2.0f);

    // draw the level boxes
    for (int i = 0; i < AMT_LVL_BOXES; i++) {
        double current_x = start_x + (i * (LVL_WIDTH + GAP_SPACE));
        double current_y = SCREEN_HEIGHT / 2.0f;
        draw_rect(current_x, SCREEN_HEIGHT / 2.0f, LVL_WIDTH, LVL_HEIGHT, Red);
        //draw_text(body_font, Black, horizontal, vertical, "1",);

        float box_left = current_x - (LVL_WIDTH / 2.0f);
        float box_right = current_x + (LVL_WIDTH / 2.0f);
        float box_top = current_y - (LVL_WIDTH / 2.0f);
        float box_bottom = current_y + (LVL_WIDTH / 2.0f);

        if (clicked){
            if (mouse_x >= box_left && mouse_x <= box_right && mouse_y >= box_top && mouse_y <= box_bottom){
                CP_Engine_SetNextGameState(game_init, game_update, game_exit);
            }
        }
	}
}

void lvlselect_exit(void) {

}