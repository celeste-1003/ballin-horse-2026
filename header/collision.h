#pragma once

#include "cprocessing.h"

// WALL COLLISION 
int check_wall_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector wall_start, CP_Vector wall_end);

CP_Vector get_wall_normal(CP_Vector ball_pos,
    CP_Vector wall_start, CP_Vector wall_end);

CP_Vector bounce_wall(CP_Vector movement_vector,
    CP_Vector normal_vector);

CP_Vector correct_wall_position(CP_Vector ball_pos, float ball_radius,
    CP_Vector wall_start, CP_Vector wall_end);

// HOLE COLLISION
int check_hole_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector hole_pos, float hole_radius);

// IRREGULAR SURFACE COLLISION | multiple shapes at once 
int check_surface_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector surface_pos[], float surface_radius[], int circle_count);