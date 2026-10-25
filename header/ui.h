// ui.h
#pragma once
#include "cprocessing.h"

typedef struct {
	float button_x, button_y, width, height;
	float radius;
	const char* label;
	CP_Color base;
	
	CP_Font font;
	float text_size;

	CP_BOOL enabled;

	// bottom 2 to be set by UI_update button
	CP_BOOL hovered;
	CP_BOOL held;
	float press_anim;
} Button;

CP_BOOL UI_updatebutton(Button* b);
void UI_drawbutton(const Button* b);