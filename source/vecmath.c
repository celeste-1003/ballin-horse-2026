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

CP_Vector MovementVector(CP_Vector DirectionVector, float PowerScale) {
	return CP_Vector_Scale(DirectionVector, PowerScale);
}

CP_Vector ReflectedVector(CP_Vector movementVector, CP_Vector normalVector) {
	//CP_Vector normV = CP_Vector_Normalize(normalVector);
	float dotProduct = CP_Vector_DotProduct(movementVector, normalVector);
	return CP_Vector_Subtract(movementVector, CP_Vector_Scale(normalVector, 2.0f * dotProduct));

}

CP_Vector SlideVector(CP_Vector movementVector, CP_Vector normalVector) {
	float dotProduct = CP_Vector_DotProduct(movementVector, normalVector);
	return CP_Vector_Subtract(movementVector, CP_Vector_Scale(normalVector, dotProduct));
}

CP_Vector ClosestPoint(CP_Vector point, CP_Vector lineStart, CP_Vector lineEnd)
{
	CP_Vector lineVector = CP_Vector_Subtract(lineEnd, lineStart);
	CP_Vector startToPoint = CP_Vector_Subtract(point, lineStart);

	float lineLength = CP_Vector_DotProduct(lineVector, lineVector);
	if (lineLength < 0.001f) {
		return lineStart;
	}

	float along = CP_Vector_DotProduct(startToPoint, lineVector) / lineLength;
	along = CP_Math_ClampFloat(along, 0.0f, 1.0f);

	return CP_Vector_Add(lineStart, CP_Vector_Scale(lineVector, along));
}