// ui.c
#include "cprocessing.h"
#include "header/ui.h"
#include "header/assets.h"

CP_BOOL UI_updatebutton(Button* b) {

	float mouse_x = CP_Input_GetMouseX(), mouse_y = CP_Input_GetMouseY();
	CP_BOOL over = (mouse_x >= b->button_x && mouse_x <= b->button_x + b->width && mouse_y >= b->button_y && mouse_y <= b->button_y + b->height);
	b->hovered = b->enabled && over;
	//remarks: if b->disabled, button is disabled, player cannot interact with it even if hovered = true

	CP_BOOL clicked = FALSE;
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		b->held = b->hovered;
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		clicked = b->held && b->hovered;
		b->held = FALSE;
	}
	float target = (b->hovered && b->held) ? 1.0f : 0.0f;
	float delt_time = CP_Math_ClampFloat(14.0f * CP_System_GetDt(), 0.0f, 1.0f);
	b->press_anim += (target - b->press_anim) * delt_time;

	return clicked;
}

static CP_Color Shade(CP_Color shade_col, float strength){   
	CP_Color tgt = (strength >= 0.0f) ? CP_Color_Create(255, 255, 255, shade_col.a)
		: CP_Color_Create(0, 0, 0, shade_col.a);
	return CP_Color_Lerp(shade_col, tgt, (strength >= 0.0f) ? strength : -strength);
}

void UI_drawbutton(const Button* b) {
	CP_Settings_Save();
	CP_Settings_RectMode(CP_POSITION_CORNER);

	float press = b->press_anim;
	float drop = 4.0f * (1.0f - press); //shadow shrinks as it sinks
	float sink = 2.0f * press; //face moves down
	float x = b->button_x, y = b->button_y + sink, r = b->radius;
	//remarks: if press is 0, shadow drops by 4, button face doesnt move, if 1, shadow drops by 0, face moves down by 2

	CP_Color base = b->enabled ? b->base : Shade(b->base, -0.55f);
	CP_Color dark = Shade(base, -0.55f);
	CP_Color lite = Shade(base, 0.45f);
	//if disabled, darken base color by 55%, precalc dark and lite versions

	// soft shadow
	CP_Settings_NoStroke();
	int a1 = (int)(70.0f * (1.0f - 0.6f * press));
	int a2 = (int)(110.0f * (1.0f - 0.6f * press));
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, a1));
	CP_Graphics_DrawRectAdvanced(b->button_x + 1, b->button_y + drop + 2, b->width, b->height, 0, r);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, a2));
	CP_Graphics_DrawRectAdvanced(b->button_x, b->button_y + drop, b->width, b->height, 0, r);

	// body
	CP_Settings_Fill(base);
	CP_Graphics_DrawRectAdvanced(x, y, b->width, b->height, 0, r);

	// glosssy reflection
	CP_Color gloss = lite;
	gloss.a = 70;
	CP_Settings_Fill(gloss);
	CP_Graphics_DrawRectAdvanced(x + 2, y + 2, b->width - 4, b->height * 0.45f, 0, r);

	// edge lighting
	CP_Settings_StrokeWeight(1.0f);
	CP_Settings_NoFill();
	CP_Settings_Stroke((press > 0.5f) ? dark : lite);
	CP_Graphics_DrawLine(x + r, y + 1.5f, x + b->width - r, y + 1.5f);
	CP_Graphics_DrawLine(x + r, y + b->height - 1.5f, x + b->width - r, y + b->height - 1.5f);

	// outer rim
	CP_Settings_Stroke(dark);
	CP_Settings_StrokeWeight(2.0f);
	CP_Graphics_DrawRectAdvanced(x, y, b->width, b->height, 0, r);

	// label
	CP_Font_Set(b->font);
	CP_Settings_TextSize(b->text_size);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	float cx = x + b->width * 0.5f, cy = y + b->height * 0.5f;

	CP_Settings_Fill(dark);
	CP_Font_DrawText(b->label, cx, cy + 1.0f);

	CP_Settings_Fill(b->enabled ? White : Shade(White, -0.3f));
	CP_Font_DrawText(b->label, cx, cy);

	CP_Settings_Restore();
}