#pragma once

// to be rewritten and redeclared in draw.h

void draw_rect(float x, float y, float width, float height, CP_Color col);

void draw_text(CP_Font font, CP_Color col, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v,
	const char* text, float txt_x, float txt_y);

void draw_line(float line_x1, float line_y1, float line_x2, float line_y2, float line_deg, CP_Color col);

void draw_image(CP_Image img, float img_x, float img_y, float img_width, float img_height, int alpha);

void draw_dotted_line(float x1, float y1, float x2, float y2, float spacing, float dot_diameter, CP_Color col); // can this even be done tbh

void draw_circ(float cx, float cy, float cd, CP_Color col);