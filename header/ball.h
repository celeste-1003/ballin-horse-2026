#ifndef BALL_H
#define BALL_H

#include <stdbool.h>

//typedef struct {
//    float x;
//    float y;
//} Vector2D;

typedef struct {
    CP_Vector position;
    CP_Vector velocity;
    float radius;

    // Slingshot / Aiming state
    bool is_aiming;
    CP_Vector drag_start;    // Point where the user clicked/started pulling
    CP_Vector drag_current;  // Current mouse/touch drag position

    // Physical attributes
    float friction;         // Velocity multiplier per second (e.g., 0.95f)
    float min_stop_speed;   // Velocity threshold to snap to complete rest
    float power_multiplier; // Converts pull vector magnitude to launch velocity
    float max_pull_distance;// Maximum allowed drag distance
} Ball;

// Lifecycle & Control
void Ball_Init(Ball* ball, CP_Vector position, float radius);
void Ball_Update(Ball* ball, float delta_time);
void Draw_Player(CP_Image img, CP_Vector position, float img_width, float img_height);

// Input Handling (Pull-back slingshot mechanic)
void Ball_OnPointerDown(Ball* ball, CP_Vector position);
void Ball_OnPointerMove(Ball* ball, CP_Vector position);
void Ball_OnPointerUp(Ball* ball);

// State Checks
bool Ball_IsMoving(const Ball* ball);
bool Ball_IsAiming(const Ball* ball);



#endif // BALL_H