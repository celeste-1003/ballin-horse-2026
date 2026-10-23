#include <math.h>
#include "cprocessing.h"
#include "header/constants.h"

/*!
@brief clamps least and max value -- cant be too fast or too slow so if it is out of bounds, either max or least value, uses length to compare, can always change in macros
*//*______________________________________________________________*/
CP_Vector ClampVector(CP_Vector genVector, float maxLength, float minLength) {

	float length = CP_Vector_Length(genVector);
	float CP_Math_ClampFloat(length, minLength, maxLength);

	return CP_Vector_Scale(CP_Vector_Normalize(genVector), length);
}


CP_Vector DirectionVector(CP_Vector pullVector) {

	if (CP_Vector_Length(pullVector) < MIN_DRAG_DISTANCE) {

		return CP_Vector_Zero();

	}
	else return CP_Vector_Normalize(CP_Vector_Negate(pullVector));

	//must opposite direction of pullVector > normalise > return
	//CP_Vector CP_Vector_Negate(CP_Vector v);
	//return 0;
}