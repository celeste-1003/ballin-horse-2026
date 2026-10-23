#pragma once

// to be rewritten and redeclared in draw.h

void draw_rect(float x, float y, float width, float height, CP_Color col);

void draw_text(CP_Font font, CP_Color col, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v,
	const char* text, float txt_x, float txt_y);

void draw_line(void);

void draw_image(CP_Image img, float img_x, float img_y, float img_width, float img_height, int alpha);

void draw_dotted_line(void); // can this even be done tbh