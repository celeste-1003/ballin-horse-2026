#pragma once

/*!
@brief clamps least and max value -- cant be too fast or too slow so if it is out of bounds, either max or least value, uses length of vector to compare
*//*______________________________________________________________*/
CP_Vector ClampVector(CP_Vector genVector, float maxLength, float minLength);

/*!
@brief tells u direction of movement from opposite of pull vector, then gives it in a normalised value to use as a base for multiplier
*//*______________________________________________________________*/
CP_Vector DirectionVector(CP_Vector pullVector);

CP_Vector ReflectedVector(CP_Vector movementVector, CP_Vector normalVector);

CP_Vector SlideVector(CP_Vector movementVector, CP_Vector normalVector);

CP_Vector ClosestPoint(CP_Vector point, CP_Vector lineStart, CP_Vector lineEnd);

