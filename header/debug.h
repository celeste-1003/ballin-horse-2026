// debug.h
#pragma once

#include "cprocessing.h"
#include "header/constants.h"
#include "header/ball.h"
#include "header/level.h"

float debug_dt(float raw_dt);
void debug_draw(const Ball* ball, const Level* lvl, int strokes);
void debug_log(const char* fmt, ...);
CP_BOOL debug_IsOn(void);