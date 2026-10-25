#ifndef BALL_H
#define BALL_H

#include <stdbool.h>

typedef struct {
    float x;
    float y;
} Vector2D;

typedef struct {
    Vector2D position;
    Vector2D velocity;
    float radius;

    // Slingshot / Aiming state
    bool is_aiming;
    Vector2D drag_start;    // Point where the user clicked/started pulling
    Vector2D drag_current;  // Current mouse/touch drag position

    // Physical attributes
    float friction;         // Velocity multiplier per second (e.g., 0.95f)
    float min_stop_speed;   // Velocity threshold to snap to complete rest
    float power_multiplier; // Converts pull vector magnitude to launch velocity
    float max_pull_distance;// Maximum allowed drag distance
} Ball;

// Lifecycle & Control
void Ball_Init(Ball* ball, float start_x, float start_y, float radius);
void Ball_Update(Ball* ball, float delta_time);

// Input Handling (Pull-back slingshot mechanic)
void Ball_OnPointerDown(Ball* ball, float input_x, float input_y);
void Ball_OnPointerMove(Ball* ball, float input_x, float input_y);
void Ball_OnPointerUp(Ball* ball);

// State Checks
bool Ball_IsMoving(const Ball* ball);
bool Ball_IsAiming(const Ball* ball);

#endif // BALL_H