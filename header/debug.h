// debug.h
#pragma once

#include "cprocessing.h"
#include "header/ball.h"
#include "header/level.h"


// F1 Hitboxes | F2 cycle timescale | F3 Freeze | F4 Step one frame | F5 logging 
void debug_update(void); // top of game update
float debug_dt(void);
void debug_draw(const Ball* ball, const Level* lvl); // after player is drawn
void debug_log(const char* fmt, ...);

//float debug_dt(float raw_dt);
//void debug_draw(const Ball* ball, const Level* lvl, int strokes);
//void debug_log(const char* fmt, ...);
//CP_BOOL debug_IsOn(void);