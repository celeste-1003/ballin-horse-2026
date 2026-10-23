//Libraries
#include "CProcessing.h"
#include "header/draw.h"

/**
 @brief this draws a rectangle
 @remarks this takes x and y values as positions of the starting of where its being drawn,
          the height and width and color are self explanatory
 */
void draw_rect(float x, float y, float width, float height, CP_Color col) {
	CP_Settings_Fill(col);
	CP_Graphics_DrawRect(x, y, width, height);
}

/**
 @brief this draws a text (no font size yet)
 @remarks txt_x and txt_y are the x and y positions of the text respectively.
 */
void draw_text(CP_Font font, CP_Color col, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v,
	const char* text, float txt_x, float txt_y) {
	CP_Font_Set(font);
	CP_Settings_Fill(col);
	CP_Settings_TextAlignment(h, v);
	CP_Font_DrawText(text, txt_x, txt_y);
}

/**
 @brief this draws a circle
 @remarks cd is the diameter of the circle
 */
void draw_circ(float cx, float cy, float cd, CP_Color col){
    CP_Settings_Fill(col);
    CP_Graphics_DrawCircle(cx, cy, cd);
}

/**
 @brief this draws a line
 @remarks this has 2 vectors, x1y1 and x2y2
 */
void draw_line(float line_x1, float line_y1, float line_x2, float line_y2, float line_deg, CP_Color col){
    CP_Settings_Fill(col);
    CP_Graphics_DrawLineAdvanced(line_x1, line_y1, line_x2, line_y2, line_deg);
}

/**
 @brief this draws a sprite (image)
 @remarks this will be used for the horse (ball, player)
 */
void draw_image(CP_Image img, float img_x, float img_y, float img_width, float img_height, int alpha){
	CP_Image_Draw(img, img_x, img_y, img_width, img_height, alpha);
}
