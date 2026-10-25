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

const char* level1[GRID_ROW] = {
    "################################",
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
    "#..............................#",
    "#..............................#",
    "#...........................H..#",
    "#..............................#",
    "################################"
};

/* GAME STATES */
// this runs once when entering the state
void game_init(void){

}

// this runs every frame
void game_update(void) {
	Level_Draw(level1[GRID_ROW]);
	//CP_Graphics_ClearBackground(BG_Grey);
}

// this runs once when leaving the state
void game_exit(void)
{

}
