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
#define HOLE_DIAMETER (40)
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
#define MAX_DRAG_DISTANCE (150.0f)
#define MIN_DRAG_DISTANCE (2.0f)
#define MIN_SPEED (1.0f)
#define MAX_SPEED (1500.0f)
#define FRICTION_DECELERATION (250.0f)
#define GRASS_FRICTION_MULTIPLIER (1.0f) // normal friction
#define SAND_FRICTION_MULTIPLIER (2.0f) // double friction
#define ICE_FRICTION_MULTIPLIER (0.5f) //half friction