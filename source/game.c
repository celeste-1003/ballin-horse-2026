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
#include "header/ball.h"
#include "header/collision.h"

const char* level1[GRID_ROW] = {
    "################################",
    "#..............................#",
    "#..............................#",
    "#..B...........................#",
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
static Ball  ball;
static int   strokes = 0;

/* GAME STATES */
// this runs once when entering the state
void game_init(void){
    set_assets();
    Level_Load(&currentLevel, level1, 3); //placeholder par
	Ball_Init(&ball, currentLevel.ballStart, 100.0f); //placeholder radius
    pause_init();
}

// this runs every frame
void game_update(void) {

    if (CP_Input_KeyTriggered(KEY_ESCAPE)) pause_toggle();

    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    Level_Draw(&currentLevel);
    Ball_DrawAim(&ball);
    Draw_Player(CP_Image_Load("Assets/sprites/horse_golf_ball.png"), ball.position, 100.0f, 100.0f); // placeholder dimensions + assets lol variable weirdly not working gunna spank it ok
    // later: Ball_Draw(&ball), HUD draw

    float dt = CP_System_GetDt();
	CP_Vector mouseOG = GetMousePos();

	    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		    Ball_OnPointerDown(&ball, mouseOG);
	    }
	    else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		    Ball_OnPointerMove(&ball, mouseOG);
	    }

        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
            int wasAiming = Ball_IsAiming(&ball);
            Ball_OnPointerUp(&ball);
            if (wasAiming && Ball_IsMoving(&ball)) strokes++;  
        }

        Ball_Update(&ball, dt);
        ball_vs_walls(&ball, &currentLevel);

        //if (check_wall_collision(ball.position, 100.0f, GetCol(ball.position.x), GetRow(ball.position.y))) {
        //    CP_Vector direction = Ball_GetPull(&ball);
        //    CP_Vector normal = get_wall_normal(ball.position, GetCol(ball.position.x), GetRow(ball.position.y));

        //}
        //ball_vs_walls(&ball, &currentLevel);

        //if (ball_in_hole(&ball, &currentLevel.hole)) {
        //    ball.velocity = CP_Vector_Set(0.0f, 0.0f);
        //    ball.position = currentLevel.hole.pos;
        //    /* later: save strokes and par, go to the results screen */
        //}

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
