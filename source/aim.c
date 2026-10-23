#include <math.h>
#include "cprocessing.h"
#include "header/vecmath.h"
#include "header/constants.h"

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