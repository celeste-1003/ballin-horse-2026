// pause.c

#include "cprocessing.h"
#include "header/pause.h"
#include "header/ui.h"
#include "header/draw.h"
#include "header/assets.h"
#include "header/constants.h"
#include "header/game.h"

static Button resume_btn, restart_btn, lvl_btn, menu_btn;
static CP_BOOL open = FALSE;

static void make_button(Button* b, const char* label, float center_y){
    *b = (Button){0};   
    b->button_x = BUTTON_X - (PAUSE_BUTTON_W / 2);
    b->button_y = center_y - (PAUSE_BUTTON_H / 2);
    b->width = PAUSE_BUTTON_W;
    b->height = PAUSE_BUTTON_H;
    b->radius = 15.0f;
    b->label = label;
    b->base = Red;

    b->font = body_font;
    b->text_size = PAUSE_TEXT_SIZE;

    b->enabled = (body_font != NULL);
}

void pause_init(void) {
    const float step = PAUSE_BUTTON_H + PAUSE_BUTTON_GAP;
    make_button(&resume_btn, "Resume", PAUSE_FIRST_Y + 0.0f * step);
    make_button(&restart_btn, "Restart Level", PAUSE_FIRST_Y + 1.0f * step);
    make_button(&lvl_btn, "Level Select", PAUSE_FIRST_Y + 2.0f * step);
    make_button(&menu_btn, "Main Menu", PAUSE_FIRST_Y + 3.0f * step);
    open = FALSE;
}

CP_BOOL pause_is_open(void) {
    return open;
}

static void reset_button_state(void) {
    Button* all[] = { &resume_btn, &restart_btn, &lvl_btn, &menu_btn };
    for (int i = 0; i < 4; i++) {
        all[i]->hovered = FALSE;
        all[i]->held = FALSE;
        all[i]->press_anim = 0.0f;
    }
}

void pause_toggle(void) {
    open = !open;
    if (open) reset_button_state();
}

pause_action pause_update(void) {
    pause_action action = PAUSE_NONE;
    if (UI_updatebutton(&resume_btn)) {
        return PAUSE_RESUME;
    }
    if (UI_updatebutton(&restart_btn)) {
        return PAUSE_RESTART;
    }
    if (UI_updatebutton(&lvl_btn)) {
        return PAUSE_LEVEL_SELECT;
    }
    if (UI_updatebutton(&menu_btn)) {
        return PAUSE_MAIN_MENU;
    }
    return action;
}

void pause_draw(void) {
    //dim the game state
    CP_Settings_Save();
    CP_Settings_NoStroke();
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, PAUSE_OVERLAY));
    CP_Graphics_DrawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    CP_Settings_Restore();

    // title "PAUSED"
    CP_Settings_Save();
    CP_Settings_TextSize(PAUSE_TITLE_SIZE);
    draw_text(title_font, White,
        CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
        "PAUSED", SCREEN_WIDTH * 0.5f, PAUSE_TITLE_Y);
    CP_Settings_Restore();

    UI_drawbutton(&resume_btn);
    UI_drawbutton(&restart_btn);
    UI_drawbutton(&lvl_btn);
    UI_drawbutton(&menu_btn);
}