// Libraries
#include "cprocessing.h"
#include <math.h>
#include <stdio.h>

#include "header/mainmenu.h"
#include "header/utils.h"
#include "header/aim.h"
#include "header/assets.h"
#include "header/constants.h"
#include "header/draw.h"
#include "header/level.h"
#include "header/pause.h"
#include "header/lvlselect.h"
#include "header/game.h"

const char* level1[GRID_ROW] = {
    "################################",
    "#..............................#",
    "#..............................#",
    "#...B..........................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#...........................H..#",
    "#..............................#",
    "#..............................#",
    "################################"
};

static Level currentLevel;

/* GAME STATES */
// this runs once when entering the state
void game_init(void){
    set_assets();
    Level_Load(&currentLevel, level1, 3);
    pause_init();
}

// this runs every frame
void game_update(void) {

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) pause_toggle();

    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    Level_Draw(&currentLevel);
    // later: Ball_Draw(&ball), HUD draw

    if (pause_is_open()) {
        pause_action action = pause_update();
        pause_draw();

        switch (action) {
        case PAUSE_RESUME:
            pause_toggle();
            break;
        case PAUSE_RESTART:
            CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
            break;
        case PAUSE_LEVEL_SELECT:
            CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
            break;
        case PAUSE_MAIN_MENU:
            CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
            break;
        default:
            break;
        }
        return;                 
    }
}

// this runs once when leaving the state
void game_exit(void)
{

}
