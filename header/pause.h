// pause.h
#pragma once
#include "cprocessing.h"

typedef enum {
    PAUSE_NONE = 0,
    PAUSE_RESUME,
    PAUSE_RESTART,
    PAUSE_LEVEL_SELECT,
    PAUSE_MAIN_MENU
} pause_action;

void pause_init(void);
CP_BOOL pause_is_open(void);
void pause_toggle(void);
pause_action pause_update(void);
void pause_draw(void);
