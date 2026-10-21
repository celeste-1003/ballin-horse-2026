#pragma once

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

/*!
@brief
*//*______________________________________________________________*/
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

void draw_rect(float x, float y, float width, float height, CP_Color col);

void draw_text(CP_Font font, CP_Color col, CP_TEXT_ALIGN_HORIZONTAL h, CP_TEXT_ALIGN_VERTICAL v,
	const char* text, float txt_x, float txt_y);

/*!
@brief get mouse position, used in vectors so that u dont have to keep getting x and y value seperately, result is a vector point so can feed into other cprocessing vector functions
*//*______________________________________________________________*/
CP_Vector GetMousePos(void);

/*!
@brief clamps least and max value -- cant be too fast or too slow so if it is out of bounds, either max or least value, uses length of vector to compare
*//*______________________________________________________________*/
CP_Vector ClampVector(CP_Vector genVector, float maxLength, float minLength);

/*!
@brief 
*//*______________________________________________________________*/
CP_Vector PullVector(CP_Vector startPoint, CP_Vector endPoint);

/*!
@brief power_scaling, how drag distance = launch speed
*//*______________________________________________________________*/
float PowerScale(CP_Vector pullVector);

/*!
@brief tells u direction of movement from opposite of pull vector, then gives it in a normalised value to use as a base for multiplier
*//*______________________________________________________________*/
CP_Vector DirectionVector(CP_Vector pullVector);


/*!
@brief applies friction to movement vector that slows horse fella down depending on how long it moves
*//*______________________________________________________________*/
CP_Vector ApplyFriction(CP_Vector movementVector, float deltaTime);