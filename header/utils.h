#pragma once

/*!
@brief
*//*______________________________________________________________*/
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

/*!
@brief
*//*______________________________________________________________*/
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

/*!
@brief get mouse position, used in vectors so that u dont have to keep getting x and y value seperately, result is a vector point so can feed into other cprocessing vector functions
*//*______________________________________________________________*/
CP_Vector GetMousePos(void);

/*!
@brief applies friction to movement vector that slows horse fella down depending on how long it moves
*//*______________________________________________________________*/
CP_Vector ApplyFriction(CP_Vector movementVector, float deltaTime);