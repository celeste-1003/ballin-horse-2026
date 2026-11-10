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

// Confirmation State & Buttons
static pause_action pending_action = PAUSE_NONE;
static Button btn_confirm_yes, btn_confirm_no;

static void make_button(Button* b, const char* label, float center_y) {
    *b = (Button){ 0 };
    b->button_x = BUTTON_X - (PAUSE_BUTTON_W / 2.0f);
    b->button_y = center_y - (PAUSE_BUTTON_H / 2.0f);
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
    pending_action = PAUSE_NONE;

    // Confirmation Buttons
    const float modal_y = (float)SCREEN_HEIGHT / 2.0f;
    const float btn_w = 140.0f;
    const float btn_h = 55.0f;
    const float btn_gap = 40.0f;

    btn_confirm_yes = (Button){ 0 };
    btn_confirm_yes.width = btn_w;
    btn_confirm_yes.height = btn_h;
    btn_confirm_yes.button_x = (SCREEN_WIDTH / 2.0f) - btn_w - (btn_gap / 2.0f);
    btn_confirm_yes.button_y = modal_y + 45.0f;
    btn_confirm_yes.radius = 15.0f;
    btn_confirm_yes.label = "Yes";
    btn_confirm_yes.base = Red;
    btn_confirm_yes.font = body_font;
    btn_confirm_yes.text_size = 36.0f;
    btn_confirm_yes.enabled = (body_font != NULL);

    btn_confirm_no = (Button){ 0 };
    btn_confirm_no.width = btn_w;
    btn_confirm_no.height = btn_h;
    btn_confirm_no.button_x = (SCREEN_WIDTH / 2.0f) + (btn_gap / 2.0f);
    btn_confirm_no.button_y = modal_y + 45.0f;
    btn_confirm_no.radius = 15.0f;
    btn_confirm_no.label = "No";
    btn_confirm_no.base = Brown;
    btn_confirm_no.font = body_font;
    btn_confirm_no.text_size = 36.0f;
    btn_confirm_no.enabled = (body_font != NULL);
}

CP_BOOL pause_is_open(void) {
    return open;
}

static void reset_button_state(void) {
    Button* all[] = { &resume_btn, &restart_btn, &lvl_btn, &menu_btn, &btn_confirm_yes, &btn_confirm_no };
    for (int i = 0; i < 6; i++) {
        all[i]->hovered = FALSE;
        all[i]->held = FALSE;
        all[i]->press_anim = 0.0f;
    }
}

void pause_toggle(void) {
    open = !open;
    if (open) {
        pending_action = PAUSE_NONE;
        reset_button_state();
    }
}

pause_action pause_update(void) {
    if (pending_action == PAUSE_NONE) {
        if (UI_updatebutton(&resume_btn)) {
            return PAUSE_RESUME;
        }
        if (UI_updatebutton(&restart_btn)) {
            pending_action = PAUSE_RESTART;
            reset_button_state();
            return PAUSE_NONE;
        }
        if (UI_updatebutton(&lvl_btn)) {
            pending_action = PAUSE_LEVEL_SELECT;
            reset_button_state();
            return PAUSE_NONE;
        }
        if (UI_updatebutton(&menu_btn)) {
            pending_action = PAUSE_MAIN_MENU;
            reset_button_state();
            return PAUSE_NONE;
        }
    }
    else {
        if (UI_updatebutton(&btn_confirm_yes)) {
            pause_action chosen = pending_action;
            pending_action = PAUSE_NONE;
            return chosen;
        }
        if (UI_updatebutton(&btn_confirm_no)) {
            pending_action = PAUSE_NONE;
            reset_button_state();
            return PAUSE_NONE;
        }
    }

    return PAUSE_NONE;
}

void pause_draw(void) {
    // Dim the game state
    CP_Settings_Save();
    CP_Settings_NoStroke();
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, PAUSE_OVERLAY));
    CP_Graphics_DrawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    CP_Settings_Restore();

    // Title "PAUSED"
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

    // Confirmation overlay
    if (pending_action != PAUSE_NONE) {
        CP_Settings_Save();
        CP_Settings_NoStroke();
        CP_Settings_RectMode(CP_POSITION_CORNER);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 180));
        CP_Graphics_DrawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        const float modal_w = 780.0f;
        const float modal_h = 240.0f;
        const float modal_cx = (float)SCREEN_WIDTH / 2.0f;
        const float modal_cy = (float)SCREEN_HEIGHT / 2.0f;

        CP_Settings_RectMode(CP_POSITION_CENTER);
        CP_Settings_Fill(CP_Color_Create(30, 30, 30, 255));
        CP_Settings_Stroke(CP_Color_Create(220, 220, 220, 255));
        CP_Settings_StrokeWeight(3.0f);
        CP_Graphics_DrawRect(modal_cx, modal_cy, modal_w, modal_h);

        CP_Settings_TextSize(30.0f);
        draw_text(title_font, White, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
            "Are you sure you want to go back?", modal_cx, modal_cy - 45.0f);

        CP_Settings_TextSize(24.0f);
        draw_text(body_font, Red, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE,
            "Your record will not be saved.", modal_cx, modal_cy - 5.0f);
        CP_Settings_Restore();

        UI_drawbutton(&btn_confirm_yes);
        UI_drawbutton(&btn_confirm_no);
    }
}