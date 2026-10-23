#include <math.h>
#include "cprocessing.h"

//#define DELTA_TIME 

#define MAX_DRAG_DISTANCE 150.0f
#define MIN_DRAG_DISTANCE 2.0f

// this function checks if a point is within a rectangular area 
// used for buttons and other rectangular objects
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// calculate rectangle
	float left_edge = area_center_x - (area_width / 2.0);
	float right_edge = area_center_x + (area_width / 2.0);
	float top_edge = area_center_y - (area_height / 2.0);
	float bottom_edge = area_center_y + (area_height / 2.0);

	// calculate if click point is within the boundary
	if (click_x >= left_edge && click_x <= right_edge &&
		click_y >= top_edge && click_y <= bottom_edge) {
		
		return 1;
	}
	else {

		return 0;
	}

}

// this function checks if a point is within a circle
// Used to check if player touches the sprite of horse ok
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	// calculate radius
	float radius = diameter / 2;

	// calculate distance between center and click point
	float dx = click_x - circle_center_x;
	float dy = click_y - circle_center_y;
	float d_squared = (dx * dx) + (dy * dy);

	// compare squared distance to squared radius
	if (d_squared <= (radius * radius)) {return 1;}
	else {return 0;}
}

/*!
@brief get mouse position, used in vectors so that u dont have to keep getting x and y value seperately, result is a vector point so can feed into other cprocessing vector functions
*//*______________________________________________________________*/
CP_Vector GetMousePos(void) {
	
	//gets position x and y of mouse at point function called
	float mx = CP_Input_GetMouseX();
	float my = CP_Input_GetMouseY();

	//draws it as a vector point and returns value
	return CP_Vector_Set(mx, my);
}

/*!
@brief clamps least and max value -- cant be too fast or too slow so if it is out of bounds, either max or least value, uses length to compare, can always change in macros
*//*______________________________________________________________*/
CP_Vector ClampVector(CP_Vector genVector, float maxLength, float minLength) {

	float length = CP_Vector_Length(genVector);
	float CP_Math_ClampFloat(length, minLength, maxLength);

	return CP_Vector_Scale(CP_Vector_Normalize(genVector), length);
}

/*!
@brief
*//*______________________________________________________________*/
CP_Vector PullVector(CP_Vector startPoint, CP_Vector endPoint) {

	CP_Vector pull = CP_Vector_Subtract(endPoint, startPoint);
	return ClampVector(pull, MAX_DRAG_DISTANCE, MIN_DRAG_DISTANCE);
}

float PowerScale(CP_Vector pullVector) {
	
	//find distance, distance/max_distance * 100
	return 0;
}

CP_Vector DirectionVector(CP_Vector pullVector) {

	if (CP_Vector_Length(pullVector) < MIN_DRAG_DISTANCE) {

		return CP_Vector_Zero();

	} else return CP_Vector_Normalize(CP_Vector_Negate(pullVector));

	//must opposite direction of pullVector > normalise > return
	//CP_Vector CP_Vector_Negate(CP_Vector v);
	//return 0;
}

CP_Vector ApplyFriction(CP_Vector movementVector, float deltaTime) {
	//return 0;
}