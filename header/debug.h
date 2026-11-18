// debug.h
#pragma once

#include "cprocessing.h"
#include "header/ball.h"
#include "header/level.h"
#ifdef _DEBUG

// F1 Hitboxes | F2 cycle timescale | F3 Freeze | F4 Step one frame | F5 logging 
void debug_update(void); // top of game update
float debug_dt(void);
void debug_draw(const Ball* ball, const Level* lvl); // after player is drawn
void debug_log(const char* fmt, ...);
void debug_status(void);

//float debug_dt(float raw_dt);
//void debug_draw(const Ball* ball, const Level* lvl, int strokes);
//void debug_log(const char* fmt, ...);
//CP_BOOL debug_IsOn(void);

#else // !_DEBUG

// Release build: debug.c compiles to nothing, so these stand-ins keep the
// call sites in game.c / collision.c valid and get compiled away to no-ops.
static __inline void debug_update(void) { }
static __inline void debug_status(void) { }
static __inline float debug_dt(void) { return CP_System_GetDt(); } // caller still clamps to MAX_DT
static __inline void debug_draw(const Ball* ball, const Level* lvl) { (void)ball; (void)lvl; }
#define debug_log(...) ((void)0)

#endif