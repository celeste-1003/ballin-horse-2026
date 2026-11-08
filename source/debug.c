// debug.c
#include <stdio.h>
#include <stdarg.h>

#include "cprocessing.h"
#include "header/debug.h"
#include "header/constants.h"
#include "header/collision.h"
#include "header/utils.h"
#include "header/assets.h"

#define SCALE_COUNT (3)

static CP_BOOL show_hitboxes = FALSE;
static CP_BOOL log_on = FALSE;
static CP_BOOL frozen = FALSE;
static CP_BOOL step_once = FALSE;
static int scale_index = 0;
static const float scales[SCALE_COUNT] = { 1.0f, 0.5f, 0.25f };

static void status_line_draw(const char* text, int slot, CP_Color col) {
	float y_pos = DEBUG_STATUS_TOP + (float)slot * DEBUG_STATUS_LINE_SPACE;

	CP_Settings_TextSize(DEBUG_STATUS_SIZE);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_TOP);

	// shadow shadow
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 190));
	CP_Font_DrawText(text, DEBUG_STATUS_RIGHT + 1.0f, y_pos + 1.0f);

	CP_Settings_Fill(col);
	CP_Font_DrawText(text, DEBUG_STATUS_RIGHT, y_pos);
}

/* STATUS BAR (RIGHT JUSTIFIED) */
void debug_status(void) {
	typedef struct {
		char text[48];
		CP_Color col;
	} DebugLine;

	DebugLine strip[DEBUG_STATUS_MAX];
	int n = 0;

	if (body_font == NULL) return;

	if (!show_hitboxes && !log_on && !frozen && scale_index == 0) return; // if nothings on, dont draw
	sprintf_s(strip[n].text, sizeof(strip[n].text), "DEBUG MODE");
	strip[n].col = CP_Color_Create(120, 255, 140, 235);
	n++;

	if (show_hitboxes) {
		sprintf_s(strip[n].text, sizeof(strip[n].text), "F1  hitboxes");
		strip[n].col = CP_Color_Create(0, 255, 255, 235);
		n++;
	}

	if (frozen) {
		sprintf_s(strip[n].text, sizeof(strip[n].text), "F3  frozen (F4 = step)");
		strip[n].col = CP_Color_Create(255, 190, 60, 235);
		n++;
	}

	else if (scale_index != 0) {
		sprintf_s(strip[n].text, sizeof(strip[n].text), "F2 time x%.2f", scales[scale_index]);
		strip[n].col = CP_Color_Create(255, 190, 60, 235);
		n++;
	}

	if (log_on) {
		sprintf_s(strip[n].text, sizeof(strip[n].text), "F5 Logging");
		strip[n].col = CP_Color_Create(190, 190, 190, 235);
		n++;
	}

	CP_Settings_Save();
	CP_Font_Set(body_font);
	for (int i = 0; i < n; i++) {
		status_line_draw(strip[i].text, i, strip[i].col);
	}
	CP_Settings_Restore();
}

/* INPUT */
void debug_update(void) {
	step_once = FALSE;
	
	if (CP_Input_KeyTriggered(KEY_F1)) {
		show_hitboxes = !show_hitboxes;
		debug_log("hitboxes: %s", show_hitboxes ? "on" : "off");
	}
	if (CP_Input_KeyTriggered(KEY_F2)) {
		scale_index = (scale_index + 1) % SCALE_COUNT;
		debug_log("time scale x%.2f", scales[scale_index]);
	}
	if (CP_Input_KeyTriggered(KEY_F3)) {
		frozen = !frozen;
		debug_log("frozen: %s", frozen ? "yes" : "no");
	}
	if (CP_Input_KeyTriggered(KEY_F4) && frozen) {
		step_once = TRUE;
	}
	if (CP_Input_KeyTriggered(KEY_F5)) {
		if (log_on) debug_log("logging off");
		log_on = !log_on;
		if (log_on) debug_log("logging on");
	}
}

/* TIME CONTROL */
float debug_dt(void) {
	float dt = CP_System_GetDt();
	if (dt > MAX_DT) dt = MAX_DT;

	if (frozen) return step_once ? DEBUG_STEP_DT : 0.0f;
	return dt * scales[scale_index];
}

/* HITBOXES */
static void outline_rect(float x, float y, float w, float h, CP_Color col) {
	CP_Settings_Stroke(col);
	CP_Graphics_DrawRect(x, y, w, h);
}

void debug_draw(const Ball* ball, const Level* lvl) {
	debug_status();

	if (!show_hitboxes) return;

	CP_Vector p = ball->position;
	float r = ball->radius;

	//same tile range ballCollision scans
	int min_col = GetCol(p.x - r);
	int max_col = GetCol(p.x + r);
	int min_row = GetRow(p.y - r);
	int max_row = GetRow(p.y + r);

	CP_Settings_Save();
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_NoFill();
	CP_Settings_StrokeWeight(2.0f);

	//tile scan box
	outline_rect((float)(min_col * TILE_SIZE),
		(float)(min_row * TILE_SIZE),
		(float)((max_col - min_col + 1) * TILE_SIZE),
		(float)((max_row - min_row + 1) * TILE_SIZE),
		CP_Color_Create(255, 255, 255, 60));

	// solid tiles in scan box: red + touching the ball
	for (int row = min_row; row <= max_row; row++) {
		for (int col = min_col; col <= max_col; col++) {
			if (!is_wall_tile(lvl, col, row)) continue;
			
			int hit = check_wall_collision(p, r, col, row);
			outline_rect((float)(col * TILE_SIZE), 
				(float)(row * TILE_SIZE), 
				TILE_SIZE, TILE_SIZE, 
				hit ? CP_Color_Create(255, 60, 60, 255) 
					: CP_Color_Create(255, 255, 255, 120));
		}
	}

	// tile under ball's centre
	outline_rect((float)(GetCol(p.x) * TILE_SIZE), 
		(float)(GetRow(p.y) * TILE_SIZE), 
		TILE_SIZE, TILE_SIZE, 
		CP_Color_Create(255, 0, 255, 255));

	//ball
	CP_Settings_Stroke(CP_Color_Create(0, 255, 255, 220));
	CP_Graphics_DrawCircle(p.x, p.y, r * 2.0f);

	//hole and radius where ball counts as in
	CP_Settings_Stroke(CP_Color_Create(255, 215, 0, 255));
	CP_Graphics_DrawCircle(lvl->hole.position.x, lvl->hole.position.y, (float)HOLE_DIAMETER);
	CP_Settings_Stroke(CP_Color_Create(255, 215, 0, 100));
	CP_Graphics_DrawCircle(lvl->hole.position.x, lvl->hole.position.y, (r + HOLE_DIAMETER * 0.5f) * 2.0f);

	CP_Settings_Restore();
}

void debug_log(const char* fmt, ...) {
	if (!log_on || fmt == NULL) return;

	printf("[%7.2fs]", CP_System_GetSeconds());

	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
}