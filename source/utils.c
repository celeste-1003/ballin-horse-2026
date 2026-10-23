#include <math.h>
#include "cprocessing.h"
#include "header/vecmath.h"
#include "header/constants.h"

//#define DELTA_TIME 

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


CP_Vector ApplyFriction(CP_Vector movementVector, float deltaTime) {
	//return 0;
}