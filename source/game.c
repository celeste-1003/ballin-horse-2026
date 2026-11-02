// Libraries
#include "cprocessing.h"
#include <math.h>
#include <stdbool.h>
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
#include "header/gamedata.h"
#include "header/ui.h"

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

const char* level2[GRID_ROW] = {
    "################################",
    "#..............................#",
    "#.............B................#",
    "#..............................#",
    "#.x..x..x..x...................#",
    "#############............S.....#",
    "#........................S.....#",
    "#........................S.....#",
    "#....................SSSSS.....#",
    "#..............................#",
    "#....H.........................#",
    "#.xxxxx..............###########",
    "##########...........##........#",
    "#....................##........#",
    "#....................##........#",
    "#..............................#",
    "#..............................#",
    "################################"
};

const char* level3[GRID_ROW] = {
    "################################",
    "#.........swws.................#",
    "#.........swws.................#",
    "#..B......swws.................#",
    "#.........swws....ssssssss.....#",
    "#.........ssss....swwwwwws.....#",
    "#.........ssss....swwwwwws.....#",
    "#.........swws....swwwwwws.ssss#",
    "#.........swws....swwwwwws.ssss#",
    "#.........swws....swwwwwws.ssss#",
    "#.........swws....ssssssss.....#",
    "#.....................swws.....#",
    "#....ssss.............swws.....#",
    "#.....................ssss.....#",
    "#.....................swws..H..#",
    "#.....................swws.....#",
    "#.....................swws.....#",
    "################################"
};

int g_selectedLevel = 0;
static const char** layouts[] = { level1, level2, level3 };
static const int    pars[] = { 3, 4, 5 };
static Level currentLevel;
static Ball  ball;
static int   strokes = 0;

// Victory overlay state and buttons
static bool isLevelWon = false;
static Button btn_next_level;
static Button btn_lvl_select;

/* GAME STATES */

void game_init(void) {
    set_assets();
    strokes = 0;
    isLevelWon = false;

    Level_Load(&currentLevel, layouts[g_selectedLevel], pars[g_selectedLevel]);
    Ball_Init(&ball, currentLevel.ballStart, 50.0f);
    pause_init();

    // Option A: "Next Level" Button
    btn_next_level.width = 240.0f;
    btn_next_level.height = 60.0f;
    btn_next_level.button_x = (SCREEN_WIDTH / 2.0f) - (btn_next_level.width / 2.0f);
    btn_next_level.button_y = (SCREEN_HEIGHT / 2.0f) - 15.0f;
    btn_next_level.radius = 12.0f;
    btn_next_level.label = "Next Level";
    btn_next_level.base = Red;
    btn_next_level.font = body_font;
    btn_next_level.text_size = 28.0f;
    btn_next_level.enabled = TRUE;
    btn_next_level.press_anim = 0.0f;

    // Option B: "Level Select" Button
    btn_lvl_select.width = 240.0f;
    btn_lvl_select.height = 60.0f;
    btn_lvl_select.button_x = (SCREEN_WIDTH / 2.0f) - (btn_lvl_select.width / 2.0f);
    btn_lvl_select.button_y = (SCREEN_HEIGHT / 2.0f) + 65.0f;
    btn_lvl_select.radius = 12.0f;
    btn_lvl_select.label = "Level Select";
    btn_lvl_select.base = CP_Color_Create(70, 70, 70, 255);
    btn_lvl_select.font = body_font;
    btn_lvl_select.text_size = 28.0f;
    btn_lvl_select.enabled = TRUE;
    btn_lvl_select.press_anim = 0.0f;
}

void game_update(void) {
    if (CP_Input_KeyTriggered(KEY_ESCAPE) && !isLevelWon) {
        pause_toggle();
    }

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

    // Draw game world
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    Level_Draw(&currentLevel);
    Ball_DrawAim(&ball);
    Draw_Player(CP_Image_Load("Assets/sprites/horse_golf_ball.png"), ball.position, 100.0f, 100.0f);

    // --- STAGE CLEARED OVERLAY ---
    if (isLevelWon) {
        // Darken background
        CP_Settings_RectMode(CP_POSITION_CORNER);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 180));
        CP_Graphics_DrawRect(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

        // Header text
        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        CP_Settings_TextSize(52.0f);
        CP_Font_DrawText("STAGE CLEARED!", SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - 100.0f);

        // Option A: "Next Level" button button to go next stage (TO BE CHANGED)
        if (g_selectedLevel + 1 < AMT_LVL_BOXES) {
            UI_drawbutton(&btn_next_level);
            if (UI_updatebutton(&btn_next_level)) {
                g_selectedLevel++;
                CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
                return;
            }
        }

        //  "Level Select" button to go next stage (TO BE CHANGED)
        UI_drawbutton(&btn_lvl_select);
        if (UI_updatebutton(&btn_lvl_select)) {
            CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
            return;
        }

        return; // Halt physics updates while on victory screen
    }

    // Normal ball control & simulation
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
        if (wasAiming && Ball_IsMoving(&ball)) {
            strokes++;
        }
    }

    Ball_Update(&ball, dt);
    ballCollision(&ball, &currentLevel);
    ballFriction(&ball, &currentLevel);

    // Win condition check: Ball inside hole radius
    float dx = ball.position.x - currentLevel.hole.position.x;
    float dy = ball.position.y - currentLevel.hole.position.y;
    float dist_sq = (dx * dx) + (dy * dy);
    float hole_radius = (float)HOLE_DIAMETER / 2.0f;

    if (dist_sq <= (hole_radius * hole_radius)) {
        ball.velocity = CP_Vector_Set(0.0f, 0.0f);
        ball.position = currentLevel.hole.position;

        // Persist stage unlock progress
        GameData_OnStageCleared(g_selectedLevel + 1);

        // Activate victory overlay
        isLevelWon = true;
    }
}

void game_exit(void) {

}