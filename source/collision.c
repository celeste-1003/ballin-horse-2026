#include <math.h>
#include "cprocessing.h"
#include "header/collision.h"
#include "header/vecmath.h"
#include "header/constants.h"
#include "header/utils.h"
#include "header/ball.h"
#include "header/level.h"
#include "header/mainmenu.h"

// WALL COLLISION CHECK | Uses closest point on line segment to ball center to determine if collision has occurred
int check_wall_collision(CP_Vector ball_pos, float ball_radius,
    int col, int row) {

    // Calculate the boundaries of the wall tile
    float left = (float)(col * TILE_SIZE);
    float right = left + TILE_SIZE;
    float top = (float)(row * TILE_SIZE);
    float bottom = top + TILE_SIZE;

    // Find the closest point on the rectangle to the ball
    float closest_x = CP_Math_ClampFloat(ball_pos.x, left, right);
    float closest_y = CP_Math_ClampFloat(ball_pos.y, top, bottom);

    // Calculate squared distance between ball and closest point
    float dx = ball_pos.x - closest_x;
    float dy = ball_pos.y - closest_y;

    float distance_squared = dx * dx + dy * dy;

    // Check if distance is within the ball's radius
    if (distance_squared <= ball_radius * ball_radius) {
        return 1;
    }

    return 0;
}


// GET WALL NORMAL | Needed to calculate the angle of the bounce | Used by ReflectedVector() to calculate bounce direction
CP_Vector get_wall_normal(CP_Vector ball_pos,
    int col, int row) {

    // Calculate tile boundaries
    float left = (float)(col * TILE_SIZE);
    float right = left + TILE_SIZE;
    float top = (float)(row * TILE_SIZE);
    float bottom = top + TILE_SIZE;

    // Find closest point on the tile
    float closest_x = CP_Math_ClampFloat(ball_pos.x, left, right);
    float closest_y = CP_Math_ClampFloat(ball_pos.y, top, bottom);

    CP_Vector closest_point = CP_Vector_Set(closest_x, closest_y);

    // Calculate direction from wall towards ball
    CP_Vector normal_vector = CP_Vector_Subtract(ball_pos, closest_point);

    // If ball centre is outside the wall, use that direction
    if (CP_Vector_Length(normal_vector) >= 0.001f) {
        return CP_Vector_Normalize(normal_vector);
    }

    // If ball centre is inside wall, find nearest edge
    float dist_left = ball_pos.x - left;
    float dist_right = right - ball_pos.x;
    float dist_top = ball_pos.y - top;
    float dist_bottom = bottom - ball_pos.y;

    // Initially assume left edge is closest
    float min_dist = dist_left;
    CP_Vector normal_vector_inside = CP_Vector_Set(-1.0f, 0.0f);

    // Check right edge
    if (dist_right < min_dist) {
        min_dist = dist_right;
        normal_vector_inside = CP_Vector_Set(1.0f, 0.0f);
    }

    // Check top edge
    if (dist_top < min_dist) {
        min_dist = dist_top;
        normal_vector_inside = CP_Vector_Set(0.0f, -1.0f);
    }

    // Check bottom edge
    if (dist_bottom < min_dist) {
        normal_vector_inside = CP_Vector_Set(0.0f, 1.0f);
    }

    return normal_vector_inside;
}


// WALL BOUNCE | Reflecting the ball's movement
CP_Vector bounce_wall(CP_Vector movement_vector,
    CP_Vector normal_vector) {

    // Check direction of velocity relative to wall
    float dot_product = CP_Vector_DotProduct(
        movement_vector, normal_vector);

    // Only bounce if moving towards wall
    if (dot_product < 0.0f) {

        // Reflect velocity using existing vecmath.c function
        movement_vector = ReflectedVector(
            movement_vector, normal_vector);

        // Reduce velocity after bouncing
        movement_vector = CP_Vector_Scale(
            movement_vector, WALL_BOUNCE_MULTIPLIER);
    }

    return movement_vector;
}



// CORRECT WALL POSITION | This is to move the ball out of the wall in case of overlap
CP_Vector correct_wall_position(CP_Vector ball_pos, float ball_radius,
    int col, int row) {

    // Calculate boundaries of wall tile
    float left = (float)(col * TILE_SIZE);
    float right = left + TILE_SIZE;
    float top = (float)(row * TILE_SIZE);
    float bottom = top + TILE_SIZE;

    // Find closest point on rectangle
    float closest_x = CP_Math_ClampFloat(ball_pos.x, left, right);
    float closest_y = CP_Math_ClampFloat(ball_pos.y, top, bottom);

    CP_Vector closest_point = CP_Vector_Set(closest_x, closest_y);

    // Determine direction to push ball away
    CP_Vector normal_vector = get_wall_normal(ball_pos, col, row);

    // Calculate distance between ball and wall
    float distance = CP_Vector_Distance(ball_pos, closest_point);

    // If ball centre is inside tile
    if (distance < 0.001f) {

        // Place ball outside the nearest tile edge
        if (normal_vector.x < 0.0f) {
            ball_pos.x = left - ball_radius;
        }
        else if (normal_vector.x > 0.0f) {
            ball_pos.x = right + ball_radius;
        }
        else if (normal_vector.y < 0.0f) {
            ball_pos.y = top - ball_radius;
        }
        else {
            ball_pos.y = bottom + ball_radius;
        }

        return ball_pos;
    }

    // Check if ball overlaps wall boundary
    if (distance < ball_radius) {

        // Calculate how far the ball overlaps
        float overlap = ball_radius - distance;

        // Push ball outside the wall
        ball_pos = CP_Vector_Add(
            ball_pos,
            CP_Vector_Scale(normal_vector, overlap)
        );
    }

    return ball_pos;
}


// HOLE COLLISION | Checks whether the ball touches the hole to complete the level
int check_hole_collision(CP_Vector ball_pos, float ball_radius,
    CP_Vector hole_pos, float hole_radius) {

    // Calculate distance between both circle centres
    float distance = CP_Vector_Distance(ball_pos, hole_pos);

    // Ball wins when it touches the hole
    if (distance <= ball_radius + hole_radius) {
        return 1;
    }

    return 0;
}


// SURFACE COLLISION | Returns the tile underneath the ball's centre
TileType check_surface_collision(CP_Vector ball_pos,
    const Level* lvl) {

    // Convert pixel position into grid coordinates
    int col = (int)(ball_pos.x / TILE_SIZE);
    int row = (int)(ball_pos.y / TILE_SIZE);

    // Return surface type stored in level grid
    return Level_GetTile(lvl, col, row);
}


// SURFACE FRICTION | Determines friction multiplier using current tile type
float get_friction_multiplier(CP_Vector ball_pos,
    const Level* lvl) {

    // Identify current surface
    TileType current_tile = check_surface_collision(ball_pos, lvl);

    // Sand has greater friction
    if (current_tile == tileSand) {
        return SAND_FRICTION_MULTIPLIER;
    }

    //// Ice has less friction
    //else if (current_tile == tileIce) {
    //    return ICE_FRICTION_MULTIPLIER;
    //}

    // Use normal friction for grass and other tiles
    return GRASS_FRICTION_MULTIPLIER;
}

static int is_wall_tile(const Level* lvl, int col, int row) {
    if (col < 0 || row < 0 || col >= GRID_COL || row >= GRID_ROW) {
        return 1;
    }
    return Level_GetTile(lvl, col, row) == tileWall;
}


////keep ball frm glitching out of bounds by checking
//static is_walltype(const Level* lvl, int col, int row) {
// baby doesnt work :<
//}

void ballCollision(Ball* ball, const Level* lvl) {

    // get dt first 
    float dt = CP_System_GetDt();
    if (dt > MAX_DT) {
        dt = MAX_DT;
    }


    float speed = CP_Vector_Length(ball->velocity);

    if (speed < MIN_SPEED) {
        ball->velocity = CP_Vector_Set(0.0f, 0.0f);
        if (check_hole_collision(ball->position, ball->radius, lvl->hole.position, (float)HOLE_DIAMETER/2.0))
            CP_Engine_SetNextGameStateForced(main_menu_init, main_menu_update, main_menu_exit); //placeholder first before results screen is doneeeee 
        return;
    }

    //check surface, based on surface, give me multiplier, times by multiplier

    float travel = speed * dt;
    float max_step = ball->radius * 0.5f;

    //rounds up instead of down get it ceiling instead of floor hahrharharhr
    int steps = (int)ceilf(travel / max_step);
    if (steps < 1) {
        steps = 1;
    }
    if (steps > MAX_STEPS) {
        steps = MAX_STEPS;
    }

    float sub_dt = dt / (float)steps;

    //loops and checks everytime it moves per step. so it doesnt glitch out of bounds okok
    for (int i = 0; i < steps; ++i) {
        ball->position = CP_Vector_Add(ball->position, CP_Vector_Scale(ball->velocity, sub_dt));
        if (check_surface_collision(ball->position, lvl) == tileWater)
            CP_Engine_SetNextGameStateForced(main_menu_init, main_menu_update, main_menu_exit); //placeholder first before results screen is doneeeee !
    }

    for (int check = 0; check < CHECK_TIMES; ++check) {
        //bounding box of ball !! kim u can make these lines visible when u do debugger ok.
        int min_col = (int)floorf((ball->position.x - ball->radius) / TILE_SIZE);
        int max_col = (int)floorf((ball->position.x + ball->radius) / TILE_SIZE);
        int min_row = (int)floorf((ball->position.y - ball->radius) / TILE_SIZE);
        int max_row = (int)floorf((ball->position.y + ball->radius) / TILE_SIZE);

        for (int row = min_row; row <= max_row; row++) {
            for (int col = min_col; col <= max_col; col++) {

                if (!is_wall_tile(lvl, col, row)) {
                    continue;
                }

                if (!check_wall_collision(ball->position, ball->radius, col, row)) {
                    continue;
                }

                CP_Vector normal = get_wall_normal(ball->position, col, row);
                ball->position = correct_wall_position(ball->position, ball->radius, col, row);
                ball->velocity = bounce_wall(ball->velocity, normal);
            }
        }
    }
}

void ballFriction(Ball* ball, const Level* lvl) {

    float friction = get_friction_multiplier(ball->position, lvl);
    ball->velocity = CP_Vector_Scale(ball->velocity, friction);

    if (CP_Vector_Length(ball->velocity) < MIN_SPEED) {
        ball->velocity = CP_Vector_Set(0.0f, 0.0f);
    }
}