//Libraries
#include "cprocessing.h"
#include "header/draw.h"
#include "header/constants.h"

void lvlselect_init(void) {
    CP_Settings_RectMode(CP_POSITION_CENTER);
    Red = CP_Color_Create(220, 20, 60, 255);
    BG_Grey = CP_Color_Create(128, 128, 128, 255);
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

void lvlselect_update(void) {

    CP_Graphics_ClearBackground(BG_Grey);

    // draw the level boxes
    for (int i = 0; i < AMT_LVL_BOXES; i++) {
        float total_grp_width = (AMT_LVL_BOXES * LVL_WIDTH) + ((AMT_LVL_BOXES - 1) * GAP_SPACE);
        float start_x = (1600.0f / 2.0f) - (total_grp_width / 2.0f) + (LVL_WIDTH / 2.0f);
        double current_x = start_x + (i * (LVL_WIDTH + GAP_SPACE));
        draw_rect(current_x, 450.0f, LVL_WIDTH, LVL_HEIGHT, Red);
	}

    //// check if any of the levels have been clicked (prevent player from clicking 2 if they havent cleared 1 and 3 if they havent cleared 2)
    //if (CP_Input_MouseClicked()){
    //    if (IsAreaClicked(button_x, button_y, area_width, area_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) // x y width and height arent final pls change
    //}
}

void lvlselect_exit(void) {

}