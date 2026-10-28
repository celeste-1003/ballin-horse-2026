#pragma once
#include "cprocessing.h"

// SPLASH SCREEN MACROS
#define SPLASH_COUNT (2)
#define SPLASH_HOLD_TIME (2.0f)
#define SPLASH_FADE_TIME (0.4f)
#define SPLASH_MAX_W (800.0f)
#define SPLASH_MAX_H (450.0f)

// LEVEL SELECT MACROS
#define AMT_LVL_BOXES (3)
#define LVL_WIDTH (100.0f)
#define LVL_HEIGHT (100.0f)
#define GAP_SPACE (100.0f)
#define LVL_X (650.0f)
#define LVL_Y (100.0f)

// GRID DRAWING MACROS-KEEP IT TO INT BC CONSTANT DOESNT TAKE FLOAT
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)
#define TILE_SIZE (50)
#define HOLE_DIAMETER (60)
#define GRID_COL (SCREEN_WIDTH / TILE_SIZE) //32
#define GRID_ROW (SCREEN_HEIGHT / TILE_SIZE) //18

// MAIN MENU MACROS
#define BUTTON_X (800.0f)
#define PLAY_Y (600.0f)
#define EXIT_Y (775.0f)
#define MMBUTTON_WIDTH (250.0f)
#define MMBUTTON_HEIGHT (125.0f)
#define TITLE_WIDTH (750.0f) // placeholder(?) for image
#define TITLE_HEIGHT (400.0f)
#define TITLE_Y (275.0f)
#define BUTTON_TEXT_SIZE (70.0f)

// DRAGGING/GAMEPLAY MACROS
#define MAX_DT (1.0f / 30.0f)
#define CHECK_TIMES (2)
#define MAX_STEPS (16)
#define MAX_DRAG_DISTANCE (150.0f)
#define MIN_DRAG_DISTANCE (2.0f)
#define MIN_SPEED (1.0f)
#define MAX_SPEED (1500.0f)
#define FRICTION_DECELERATION (250.0f)
#define GRASS_FRICTION_MULTIPLIER (1.0f) // normal friction
#define SAND_FRICTION_MULTIPLIER (0.5f) // double friction
#define ICE_FRICTION_MULTIPLIER (0.5f) //half friction
#define WALL_BOUNCE_MULTIPLIER (0.9f) //Bounce off wall lose 10% speed

// PAUSE MENU MACROS
#define PAUSE_OVERLAY (150)
#define PAUSE_TITLE_Y (130.0f)
#define PAUSE_TITLE_SIZE (80.0f)
#define PAUSE_BUTTON_W (250.0f)     
#define PAUSE_BUTTON_H (125.0f)     
#define PAUSE_BUTTON_GAP (20.0f)
#define PAUSE_FIRST_Y (260.0f)     
#define PAUSE_TEXT_SIZE (50.0f)  

// DEBUG MACROS
#define DEBUG_MAX_DT (1.0f / 3.0f)
#define DEBUG_STEP_DT (1.0f / 60.0f)
#define HUD_TXT_SIZE (18.0f)
#define HUD_X (12.0f)
#define HUD_Y (SCREEN_HEIGHT / 100.0f)
#define HUD_LINE_H (21.0f)
