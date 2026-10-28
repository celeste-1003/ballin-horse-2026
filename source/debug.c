// debug.c
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

#include "cprocessing.h"
#include "header/ball.h"
#include "header/level.h"
#include "header/constants.h"
#include "header/assets.h"
#include "header/game.h"
#include "header/debug.h"

#ifdef _WIN32
#include <windows.h>
#endif

static CP_BOOL debug_on = FALSE;
static CP_BOOL show_hits = FALSE;
static CP_BOOL frozen = FALSE;
static float time_scale = 1.0f;
static float last_raw_dt = 0.0f;

static CP_BOOL was_outside = FALSE;
static CP_BOOL warned_no_front = FALSE;

/* HELPER FUNCTIONS */

static CP_Color dbg_col(int r, int g, int b, int a) {
	return CP_Color_Create(r, g, b, a);
}

static int dbg_finite(float v) {
#ifdef _MSC_VER
	return _finite(v) != 0;
#else
	return isfinite(v) != 0;
#endif

}

static const char* dbg_tile_name(TileType t) {
	switch (t) {
	case tileGrass: return "grass";
	case tileStart: return "spawn";
	case tileWall: return "wall";
	case tileWater: return "water";
	case tileHole: return "goal";
	case tileSand: return "sand";
	default: return "?";
	}
}

static void dbg_outline_rect(float x, float y, float w, float h, CP_Color c, float weight) {
	CP_Settings_NoFill();
	CP_Settings_Stroke(c);
	CP_Settings_StrokeWeight(weight);
	CP_Graphics_DrawRectAdvanced(x, y, w, h, 0.0f, 0.0f);
}

static void dbg_outline_circle(float x, float y, float diameter, CP_Color col, float weight) {
	CP_Settings_NoFill();
	CP_Settings_Stroke(col);
	CP_Settings_StrokeWeight(weight);
	CP_Graphics_DrawCircle(x, y, diameter);
}

static void dbg_arrow(CP_Vector from, CP_Vector to, CP_Color col) {
	CP_Settings_Stroke(col);
	CP_Settings_StrokeWeight(2.0f);
	CP_Graphics_DrawLine(from.x, from.y, to.x, to.y);
	
	CP_Vector d = CP_Vector_Subtract(to, from);
	float length = CP_Vector_Length(d);
	if (length < 0.001f)return;

	d = CP_Vector_Scale(d, 1.0f / length);
	CP_Vector n = CP_Vector_Set(-d.y, d.x);
	CP_Vector base = CP_Vector_Subtract(to, CP_Vector_Scale(d, 10.0f));
	CP_Vector a = CP_Vector_Add(base, CP_Vector_Scale(n, 5.0f));
	CP_Vector b = CP_Vector_Subtract(base, CP_Vector_Scale(n, 5.0f));

	CP_Graphics_DrawLine(to.x, to.y, a.x, a.y);
	CP_Graphics_DrawLine(to.x, to.y, b.x, b.y);
}

static void dbg_text(const char* s, float x, float y, CP_Color col) {
	if (s == NULL || s[0] == '\0')return;
	CP_Settings_TextSize(HUD_TXT_SIZE);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_Fill(col);
	CP_Font_Set(body_font);
	CP_Font_DrawText(s, x, y);
}

static int dbg_col_of(float x) {
	return (int)floorf(x / (float)TILE_SIZE);
}
static int dbg_row_of(float y) {
	return(int)floorf(y / (float)TILE_SIZE);
}

/* DEBUGGERS */
// @brief Time Control
float debug_dt(float raw_dt) {
	last_raw_dt = raw_dt;

	float dt = CP_Math_ClampFloat(raw_dt, 0.0f, DEBUG_MAX_DT);
	if (!dbg_finite(dt)) dt = DEBUG_STEP_DT;

	if (CP_Input_KeyTriggered(KEY_F1)) {
		debug_on = !debug_on;
		if (debug_on) {
			debug_log("debug ON | F2 Hitboxes F3 Time F4 freeze F5 Step");
		}
	}
	if (!debug_on)return dt;

	if (CP_Input_KeyTriggered(KEY_F2)) {
		show_hits = !show_hits;
		debug_log("hitboxes %s", show_hits ? "on" : "off");
	}
	if (CP_Input_KeyTriggered(KEY_F3)) {
		if (time_scale == 1.0f) time_scale = 0.5f;
		else if (time_scale == 0.5f) time_scale = 0.25f;
		else if (time_scale == 0.25f) time_scale == 0.1f;
		else time_scale == 1.0f;
		debug_log("time scale x%.2f", time_scale);
	}
	if (CP_Input_KeyTriggered(KEY_F4)) {
		frozen != frozen;
		debug_log("frozen %s", frozen ? "yes" : "no");
	}
	if (frozen) {
		return CP_Input_KeyTriggered(KEY_F5) ? DEBUG_STEP_DT : 0.0f;
	}
	return dt * time_scale;
}

CP_BOOL Debug_IsOn(void) {
	return debug_on;
}

/* LOGGING */
// @brief this logs 
void debug_log(const char* fmt, ...) {
	if (!debug_on || fmt == NULL)return;

	char line[512];
	int n = sprintf(line, sizeof line, "[%7.2fs f%5u]", CP_System_GetSeconds(), CP_System_GetFrameRate());
	if (n < 0 || n >= (int)sizeof line) return;

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(line + n, sizeof line - (size_t)n, _TRUNCATE, fmt, ap);
	va_end(ap);

	printf("%s\n", line);
#ifdef _WIN32
	OutputDebugStringA(line);
	OutputDebugStringA("\n");
#endif
}

/* SHOW HITBOXES */
static int debug_scan_contacts(const Ball* ball, const Level* level, int bc, int br, unsigned* out_sig) {
	int hits = 0;
	unsigned sig = 0u;

	for (int r = br - 1; r <= br + 1; r++) {
		for (int c = bc - 1; c <= bc + 1;c++) {
			if (Level_GetTile(level, c, r) != tileWall) continue;
			if (!check_wall_collision(ball->position, ball->radius, c, r)) continue;

			hits++;
			sig |= 1u << ((r - br + 1) * 3 + (c - bc + 1));
		}
	}
	*out_sig = sig;
	return hits;
}

static void debug_draw_hitboxes(const Ball* ball, const Level* level, int bc, int br) {
	CP_Settings_Save();

	dbg_outline_circle(ball->position.x, ball->position.y, ball->radius * 2.0f, dbg_col(0, 255, 255, 210), 2.0f);
}




// this doesnt work, too bad!
//static int draw_hitboxes(const Ball* b, const Level* lvl, int strokes) {
//	int bc = (int)(b->position.x / TILE_SIZE);
//	int br = (int)(b->position.y / TILE_SIZE);
//	int hits = 0;
//
//	CP_Settings_Save();
//	CP_Settings_NoFill();
//	CP_Settings_StrokeWeight(2.0f);
//
//	CP_Settings_Stroke(CYAN);
//	CP_Graphics_DrawCircle(b->position.x, b->position.y, b->radius * 2.0f);
//
//	for (int r = br - 1; r <= br + 1; r++) 
//		for (int c = bc - 1; c <= bc + 1; c++) {
//			if (Level_GetTile(lvl, c, r) != tileWall) continue;
//
//			int hit = check_wall_collision(b->position, b->radius, c, r);
//			CP_Settings_Stroke(hit ? RED : WHITE_FAINT);
//			CP_Graphics_DrawRectAdvanced(c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, 0);
//
//			if (hit) {
//				hits++;
//				CP_Vector n = get_wall_normal(b->position, c, r);
//				draw_arrow(b->position, CP_Vector_Add(b->position, CP_Vector_Scale(n, 40.0f)));	
//			}
//	}
//	
//	CP_Settings_Stroke(GOLD);
//	CP_Graphics_DrawCircle(lvl->hole.pos.x, lvl->hole.pos.y, (float)HOLE_DIAMETER);
//	CP_Settings_Stroke(GOLD_FAINT);
//	CP_Settings_DrawCircle(lvl->hole.position.x, lvl->hole.position.y, (b->radius + HOLE_DIAMETER * 0.5f) * 2.0f);
//}

