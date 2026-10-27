#pragma once

#include "cprocessing.h"
#include "constants.h"
#include "level.h"
#include "header/ball.h"

// CHECK WALL COLLISION
int check_wall_collision(CP_Vector ball_pos, float ball_radius,
    int col, int row);

CP_Vector get_wall_normal(CP_Vector ball_pos,
    int col, int row);

CP_Vector bounce_wall(CP_Vector movement_vector,
    CP_Vector normal_vector);

CP_Vector correct_wall_position(CP_Vector ball_pos, float ball_radius,
    int col, int row);

// HOLE COLLISION
int check_hole_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector hole_pos, float hole_radius);

// SURFACE DETECTION
TileType check_surface_collision(CP_Vector ball_pos,
    const Level* lvl);

// SURFACE FRICTION
float get_friction_multiplier(CP_Vector ball_pos,
    const Level* lvl);

static int is_wall_tile(const Level* lvl, int col, int row);

void ballCollision(Ball* ball, const Level* lvl);

void ballFriction(Ball* ball, const Level* lvl);