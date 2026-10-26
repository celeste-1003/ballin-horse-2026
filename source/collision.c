#include <math.h>
#include "cprocessing.h"
#include "header/collision.h"
#include "header/vecmath.h"
#include "header/constants.h"
#include "header/utils.h"

// WALL COLLISION CHECK | Uses closest point on line segment to ball center to determine if collision has occurred
int check_wall_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector wall_start, CP_Vector wall_end) {

    CP_Vector closest_point = ClosestPoint(ball_pos, wall_start, wall_end);
	
    float distance = CP_Vector_Distance(ball_pos, closest_point);

    if (distance <= ball_radius) {
		return 1; //Collision detected
    }

	return 0; //No collision
}


// GET WALL NORMAL | Needed to calculate the angle of the bounce | Used by ReflectedVector() to calculate bounce direction
CP_Vector get_wall_normal(CP_Vector ball_pos,
    CP_Vector wall_start, CP_Vector wall_end) {
    //Find closest point to the wall
    CP_Vector closest_point = ClosestPoint(ball_pos, wall_start, wall_end);
	//Get the direction from the wall towards the ball | to calculate the direction of the bounce
    CP_Vector normal_vector = CP_Vector_Subtract(ball_pos, closest_point);

    // If the ball is exactly on the wall
    if (CP_Vector_Length(normal_vector) < 0.001f) {
        // Get the wall direction
        CP_Vector wall_vector = CP_Vector_Subtract(wall_end, wall_start);
        //If wall has no length, return 0 | edge case for any accidental invalid walls
        if (CP_Vector_Length(wall_vector) < 0.001f) {
            return CP_Vector_Zero();
        }

        normal_vector = CP_Vector_Set(-wall_vector.y, wall_vector.x);
    }
    //normalizing the normal to correct the 
    return CP_Vector_Normalize(normal_vector);
}


// WALL BOUNCE | Reflecting the ball's movement
CP_Vector bounce_wall(CP_Vector movement_vector,
    CP_Vector normal_vector) {
    //towards or away from the wall
    float dot_product = CP_Vector_DotProduct(movement_vector, normal_vector);

    // Negative dot product means the ball is is moving towards the wall
    if (dot_product < 0.0f) {

        movement_vector = ReflectedVector(movement_vector, normal_vector);

        // Lose some speed after bouncing | -10% speed
        movement_vector = CP_Vector_Scale(movement_vector, 0.9f);
    }

    return movement_vector;
}


// CORRECT WALL POSITION | This is to move the ball out of the wall in case of overlap
CP_Vector correct_wall_position(CP_Vector ball_pos, float ball_radius,
    CP_Vector wall_start, CP_Vector wall_end) {

    CP_Vector closest_point = ClosestPoint(ball_pos, wall_start, wall_end);

    CP_Vector normal_vector = get_wall_normal(ball_pos, wall_start, wall_end);
    // If no valid normal direction keep the original positiion
    if (CP_Vector_Length(normal_vector) < 0.001f) {
        return ball_pos;
    }

    float distance = CP_Vector_Distance(ball_pos, closest_point);

    if (distance < ball_radius) {

        float overlap = ball_radius - distance;

        ball_pos = CP_Vector_Add(
            ball_pos,
            CP_Vector_Scale(normal_vector, overlap)
        );
    }

    return ball_pos;
}


// ENVIRONMENTAL SURFACE COLLISION | if the environmental obstacles are irregular and circular shaped.
int check_surface_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector surface_pos[], float surface_radius[], int circle_count) {

    // Loop through all circles making up the surface
    for (int i = 0; i < circle_count; i++) {

        // Calculate distance between ball and current circle
        float distance = CP_Vector_Distance(ball_pos, surface_pos[i]);

        // Check if ball touches the current circle
        if (distance <= ball_radius + surface_radius[i]) {
            return 1; //
        }
    }

    // Ball does not touch any circles
    return 0;
}


// HOLE COLLISION | Checks whether the ball touches the hole to complete the level
int check_hole_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector hole_pos, float hole_radius) {

    float distance = CP_Vector_Distance(ball_pos, hole_pos);

    // The whole ball must fit inside the hole to win
    if (hole_radius >= ball_radius &&
        distance <= hole_radius - ball_radius) {
        return 1;
    }
    /*
    // Ball wins as soon as it touches the hole
    if (distance <= ball_radius + hole_radius) {
        return 1;
    }
    */
    return 0;
}