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
#include "header/debug.h"
#include "header/gameover.h"
#include "header/enemy.h"

const char* level1[GRID_ROW] = { // fastest is 2 strokes
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

const char* level2[GRID_ROW] = { // fastest is 4 strokes
    "################################", 
    "#ssss..........................#",
    "#sss......................H....#",
    "#ss............................#",
    "#s................##############",
    "#...........####################",
    "#..........#####################",
    "#.........########.............#",
    "#.........######..........B....#",
    "#.........xxxxxx...............#",
    "#..............................#",
    "#..............................#",
    "#l.............................#",
    "#ll............................#",
    "#lll...........................#",
    "######.................#########",
    "########..............##########",
    "################################"
};

const char* level3[GRID_ROW] = {
    "################################",
    "#.........#...E...#............#",
    "#.........#.......#............#",
    "#.........#...H...#............#",
    "#.........#.......#............#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#.........#########............#",
    "#..............................#",
    "#..............................#",
    "#.............B................#",
    "#..............................#",
    "#..............................#",
    "#.........lllllllll............#",
    "################################"
};

const char* level4[GRID_ROW] = {
    "###########################t####",
    "#t..........................t###",
    "#t...........................t##",
    "#t............................t#",
    "#t.......###########..........t#",
    "#t.......######sss##..........t#",
    "#x..............ss##......H...t#",
    "#x...............s##..........t#",
    "#x................##############",
    "#x................##############",
    "#x.............................#",
    "##ssssssss#....................#",
    "##ssssssss#....................#",
    "##ssssssss#....................#",
    "#wwwwwwwww#ss...............B..#",
    "#wwwwwwwww#sss.................#",
    "#wwEwwwwww#ssss................#",
    "###############tttttttttt#######"
};

const char* level5[GRID_ROW] = {
    "################################",
    "#............................E.#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..........###########.........#",
    "#..........###########.........#",
    "#...................##.........#",
    "#...............B...##.........#",
    "#...................##.........#",
    "##..................##.........#",
    "###ssssssssss#########.........#",
    "###.................xx.........#",
    "##..................xx.........#",
    "#...................ss....H....#",
    "#...................ss.........#",
    "#wwwwwwwwww#........ss.........#",
    "################################"
};

const char* level6[GRID_ROW] = {
    "################################",
    "#.........#wwwwwww#............#",
    "#.........#wwwtwww#............#",
    "#.........#wwtHtww#............#",
    "#.......E.xxx...xxx.E..........#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#...E.........B............E...#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#..............................#",
    "#.........E.......E............#",
    "#..............................#",
    "#..............................#",
    "################################"
};

int g_selectedLevel = 0;
static const char** layouts[] = { level1, level2, level3, level4, level5, level6 };
static const int    pars[AMT_LVL_BOXES] = { 3, 4, 5, 5, 6, 7 };
static Level currentLevel;
static Ball  ball;
static Enemy enemies[MAX_ENEMIES];
static int   strokes = 0;

static float flag_order_timer = 0.0f;

//static int gameoverSound = 0;
static int horseSound = 0;
static int sandSound = 0;
static int readySound = 0;

// Victory overlay state and buttons
bool isLevelWon = false;
bool isLevelLost = false;

Button btn_next_level;
Button btn_lvl_select;

Button btn_retry;
Button btn_main_menu;

static const char* level_titles[AMT_LVL_BOXES] = {
    "Level 1 - We're just getting started!",
    "Level 2 - Getting around",
    "Level 3 - Somebody's watching",
    "Level 4 - Extra Stuffs",
    "Level 5 - Which way, pardner?",
    "Level 6 - THIS IS A ROBBERY!!!",
};

typedef enum {
    INTRO_ENTER,
    INTRO_WOBBLE,
    INTRO_EXIT,
    INTRO_DONE,
}IntroPhase;

static IntroPhase intro_phase = INTRO_DONE;
static float      intro_timer = 0.0f;

// start of title draw
static void LevelTitle_Draw(void) {
    if (intro_phase == INTRO_DONE) return;

    float cx = SCREEN_WIDTH * 0.5f;
    float cy = SCREEN_HEIGHT * 0.5f;
    float x = cx;
    float y = cy;

    switch (intro_phase) {
    case INTRO_ENTER: {
        float p = intro_timer / INTRO_ENTER_TIME;
        if (p > 1.0f) p = 1.0f;
        float ease = 1.0f - powf(1.0f - p, 3.0f);   // fast start, slows into place
        y = INTRO_START_Y + (cy - INTRO_START_Y) * ease;
        break;
    }
    case INTRO_WOBBLE: {
        float p = intro_timer / INTRO_WOBBLE_TIME;
        float decay = 1.0f - 0.6f * p;              // wiggle dies down
        x += sinf(intro_timer * INTRO_WOBBLE_SPEED) * INTRO_WOBBLE_AMPLITUDE * decay;
        y += sinf(intro_timer * INTRO_WOBBLE_SPEED * 1.7f) * 6.0f * decay;
        break;
    }
    case INTRO_EXIT: {
        float p = intro_timer / INTRO_EXIT_TIME;
        if (p > 1.0f) p = 1.0f;
        float ease = p * p;  // slow start, fast drop
        y = cy + (INTRO_END_Y - cy) * ease;
        break;
    }
    default:
        return;
    }

    const char* title = level_titles[g_selectedLevel];

    CP_Settings_TextSize(INTRO_TITLE_SIZE);
    draw_text(title_font, CP_Color_Create(0, 0, 0, 170),
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE, title, x + 4.0f, y + 4.0f);
    draw_text(title_font, White,
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE, title, x, y);
}

static void LevelTitle_Update(float dt) {
    if (intro_phase == INTRO_DONE) return;

    intro_timer += dt;

    switch (intro_phase) {
    case INTRO_ENTER:
        if (intro_timer >= INTRO_ENTER_TIME) { intro_phase = INTRO_WOBBLE; intro_timer = 0.0f; }
        break;
    case INTRO_WOBBLE:
        if (intro_timer >= INTRO_WOBBLE_TIME) { intro_phase = INTRO_EXIT; intro_timer = 0.0f; }
        break;
    case INTRO_EXIT:
        if (intro_timer >= INTRO_EXIT_TIME) { intro_phase = INTRO_DONE; intro_timer = 0.0f; }
        break;
    default:
        break;
    }

    LevelTitle_Draw();
}
// end of title draw

/* GAME STATES */

void game_init(void) {

    intro_phase = INTRO_ENTER;
    intro_timer = 0.0f;

    set_assets();
    set_music_assets();

    flag_order_timer = 0.0f;

    gameover_init(); // Load result images
    //gameoverSound = 0;
    horseSound = 0;

    strokes = 0;
    isLevelWon = false; // Reset win state
    isLevelLost = false; // Reset lose state

    Level_Load(&currentLevel, layouts[g_selectedLevel], pars[g_selectedLevel]);
    Ball_Init(&ball, currentLevel.ballStart, 50.0f);
    for (int i = 0; i < currentLevel.enemyCount; i++) {
        Enemy_Init(&enemies[i], currentLevel.enemyStarts[i]);
    }
    pause_init();

    float overlay_x = (SCREEN_WIDTH - 1100.0f) / 2.0f;
    float overlay_y = (SCREEN_HEIGHT - 650.0f) / 2.0f;

    // Option B: "Level Select" Button
    btn_lvl_select.width = 240.0f;
    btn_lvl_select.height = 60.0f;
    btn_lvl_select.button_x = overlay_x + 270.0f - btn_lvl_select.width / 2.0f;
    btn_lvl_select.button_y = overlay_y + 650.0f - 70.0f - btn_lvl_select.height;
    btn_lvl_select.radius = 12.0f;
    btn_lvl_select.label = "Level Select";
    btn_lvl_select.base = CP_Color_Create(70, 70, 70, 255);
    btn_lvl_select.font = body_font;
    btn_lvl_select.text_size = 28.0f;
    btn_lvl_select.enabled = TRUE;
    btn_lvl_select.press_anim = 0.0f;

    // Option A: "Next Level" Button
    btn_next_level.width = 240.0f;
    btn_next_level.height = 60.0f;
    btn_next_level.button_x = btn_lvl_select.button_x;
    btn_next_level.button_y = btn_lvl_select.button_y - btn_next_level.height - 15.0f;
    btn_next_level.radius = 12.0f;
    btn_next_level.label = "Next Level";
    btn_next_level.base = Red;
    btn_next_level.font = body_font;
    btn_next_level.text_size = 28.0f;
    btn_next_level.enabled = TRUE;
    btn_next_level.press_anim = 0.0f;

    // Retry button for the lose screen
    btn_retry.width = 520.0f;
    btn_retry.height = 115.0f;
    btn_retry.button_x = 880.0f;
    btn_retry.button_y = 500.0f;
    btn_retry.radius = 5.0f;
    btn_retry.label = "Retry";
    btn_retry.base = CP_Color_Create(217, 144, 50, 255);
    btn_retry.font = title_font;
    btn_retry.text_size = 48.0f;
    btn_retry.enabled = TRUE;
    btn_retry.press_anim = 0.0f;

    // Main Menu button for the lose screen
    btn_main_menu.width = 300.0f;
    btn_main_menu.height = 60.0f;
    btn_main_menu.button_x = 990.0f;
    btn_main_menu.button_y = 640.0f;
    btn_main_menu.radius = 5.0f;
    btn_main_menu.label = "Main Menu";
    btn_main_menu.base = CP_Color_Create(40, 75, 99, 255);
    btn_main_menu.font = body_font;
    btn_main_menu.text_size = 30.0f;
    btn_main_menu.enabled = TRUE;
    btn_main_menu.press_anim = 0.0f;
}

void game_update(void) {
    debug_update();
    if (CP_Input_KeyTriggered(KEY_ESCAPE)
        && !isLevelWon
        && !isLevelLost) {

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

    // for tutorial png images thingy okay okay
    if (g_selectedLevel < AMT_HINTS && LVL_hint[g_selectedLevel]) {
        CP_Image_Draw(LVL_hint[g_selectedLevel], SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
    }

    // flag anims
    static const int flag_order[] = { 0,1,2,1 };
    flag_order_timer += CP_System_GetDt();
    int flag_step = (int)(flag_order_timer / 0.15f) % 4;
    int flag_frame = flag_order[flag_step];

    float sheet_W = (float)CP_Image_GetWidth(flag_sheet); // grab width and height
    float sheet_H = (float)CP_Image_GetHeight(flag_sheet);
    float frame_W = sheet_W / AMT_FLAG_FRAMES;
    float u0 = flag_frame * frame_W;
    float u1 = u0 + frame_W;

    float fw = 100.0f;
    float fh = fw * (sheet_H / frame_W);

    CP_Image_DrawSubImage(flag_sheet, currentLevel.hole.x, currentLevel.hole.y - fh / 2.0f, fw, fh, u0, 0.0f, u1, sheet_H, 255);

    Ball_DrawAim(&ball);

    Draw_Player(&ball, horse_mc, ball.position, 50.0f);
    for (int i = 0; i < currentLevel.enemyCount; i++) {
        Draw_Enemy(horse_enemy, enemies[i].position);
    }
    debug_draw(&ball, &currentLevel);

    float title_dt = CP_System_GetDt();
    if (title_dt > MAX_DT) title_dt = MAX_DT;
    LevelTitle_Update(title_dt);

    // --- STAGE CLEARED OVERLAY ---
    if (isLevelWon) {
        // Draw the new custom win overlay
        draw_win_screen();
        if (!horseSound) {
            play_rank_sound(get_gameover_rank());
            CP_Sound_PlayAdvanced(UI_win, 0.4f, 1, FALSE, CP_SOUND_GROUP_2);
            horseSound = 1;
            //gameoverSound = 1;
        }

        // Option A: "Next Level" button button to go next stage (TO BE CHANGED)
        if (g_selectedLevel + 1 < AMT_LVL_BOXES) {
            UI_drawbutton(&btn_next_level);
            if (UI_updatebutton(&btn_next_level)) {
                if (horseSound) {
                    CP_Sound_StopGroup(CP_SOUND_GROUP_2);
                    horseSound = 0;
                }
                g_selectedLevel++;
                CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
                return;
            }
        }

        //  "Level Select" button to go next stage (TO BE CHANGED)
        UI_drawbutton(&btn_lvl_select);
        if (UI_updatebutton(&btn_lvl_select)) {
            if (horseSound) {
                CP_Sound_StopGroup(CP_SOUND_GROUP_2);
                horseSound = 0;
            }
            CP_Engine_SetNextGameState(lvlselect_init, lvlselect_update, lvlselect_exit);
            return;
        }

        return; // Halt physics updates while on victory screen
    }

    if (isLevelLost) {
        // Draw the selected lose screen from gameover.c
        draw_lose_screen();
        if (!horseSound) {
            CP_Sound_PlayAdvanced(UI_youLose, 1.5, 1, FALSE, CP_SOUND_GROUP_2);
            CP_Sound_PlayAdvanced(UI_lose, 1.5, 1, FALSE, CP_SOUND_GROUP_2);
            horseSound = 1;
        }
        // Retry button
        UI_drawbutton(&btn_retry);
        if (UI_updatebutton(&btn_retry)) {
            CP_Sound_StopGroup(CP_SOUND_GROUP_2);
            horseSound = 0;
            // Restart the current level
            CP_Engine_SetNextGameStateForced(
                game_init, game_update, game_exit
            );
            return;
        }
        // Main Menu button
        UI_drawbutton(&btn_main_menu);
        if (UI_updatebutton(&btn_main_menu)) {
            CP_Sound_StopGroup(CP_SOUND_GROUP_2);
            horseSound = 0;
            // Return to main menu
            CP_Engine_SetNextGameState(
                main_menu_init, main_menu_update, main_menu_exit
            );
            return;
        }
        // Stop physics while lose screen is open
        return;
    }

    // Normal ball control & simulation
    float dt = debug_dt();
    if (dt > MAX_DT) dt = MAX_DT;
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
            CP_Sound_Play(GP_release);

            //check sand sound plz work plsplsplspslpsls work omg
            if (check_surface_collision(ball.position, &currentLevel) == tileSand) {
                CP_Sound_PlayAdvanced(GP_sand, 1.5f, 1.0f, FALSE, CP_SOUND_GROUP_1);
            }

            debug_log("shot %d, speed %.1f", strokes, CP_Vector_Length(ball.velocity));
        }
    }


    Ball_Update(&ball, dt);
    for (int i = 0; i < currentLevel.enemyCount; i++) {
        Enemy_Chase(&enemies[i], &ball, dt);
    }
    // ballCollision now returns the hazard type
    int hazard = ballCollision(&ball, enemies, &currentLevel, dt);
    // Show the corresponding lose screen if a hazard was hit
    if (hazard != 0) {
        // Water = 1 - 1 = 0
        // Spikes = 2 - 1 = 1
        gameover_set_lose(hazard - 1);
        isLevelLost = true;
        return;
    }

    // Apply surface friction if the player is still alive
    ballFriction(&ball, &currentLevel, dt);

    //check collision between ball and enemy
    for (int i = 0; i < currentLevel.enemyCount; i++) {
        float mx = ball.position.x - enemies[i].position.x;
        float my = ball.position.y - enemies[i].position.y;
        float lose_check = (mx * mx) + (my * my);
        float r = ball.radius + enemies[i].radius;


        if (lose_check <= (r*r - 50.0f)) {
            debug_log("died by enemy %d", i);
            ball.velocity = CP_Vector_Set(0.0f, 0.0f);
            gameover_set_lose(2); // Enemy lose screen
            isLevelLost = true;
            return;
        }
    }

    // Win condition check: Ball inside hole radius
    float dx = ball.position.x - currentLevel.hole.x;
    float dy = ball.position.y - currentLevel.hole.y;
    float lose_check2 = (dx * dx) + (dy * dy);
    float r2 = (HOLE_DIAMETER / 2.0f) + ball.radius;

    if (lose_check2 <= (r2*r2 + 50.0f)) {

        ball.velocity = CP_Vector_Set(0.0f, 0.0f);
        ball.position = currentLevel.hole;

        // Persist stage unlock progress
        GameData_OnStageCleared(g_selectedLevel + 1);

        // Pass the player's score to gameover.c
        gameover_set_results(currentLevel.par, strokes);

        // Activate victory overlay
        isLevelWon = true;

        return;
    }
}

void game_exit(void) {

}