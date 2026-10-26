#include "header/ball.h"
#include <math.h>

//test
static float GetDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

void Ball_Init(Ball* ball, float start_x, float start_y, float radius) {
    ball->position.x = start_x;
    ball->position.y = start_y;
    ball->velocity.x = 0.0f;
    ball->velocity.y = 0.0f;
    ball->radius = radius;

    ball->is_aiming = false;
    ball->drag_start = (Vector2D){ 0.0f, 0.0f };
    ball->drag_current = (Vector2D){ 0.0f, 0.0f };

    // Ground resistance & mechanics tuning
    ball->friction = 0.92f;           // Adjust lower for rough grass, higher for slick greens
    ball->min_stop_speed = 1.5f;       // Below this speed, the ball stops completely
    ball->power_multiplier = 6.0f;     // Shot power scaling factor
    ball->max_pull_distance = 120.0f;  // Max drag reach
}

void Ball_OnPointerDown(Ball* ball, float input_x, float input_y) {
    // Only allow initiating a shot if the ball is completely stationary
    if (Ball_IsMoving(ball)) {
        return;
    }

    // Check if the user initiated the click/touch close to the ball
    float dist = GetDistance(ball->position.x, ball->position.y, input_x, input_y);
    if (dist <= ball->radius * 2.0f) {
        ball->is_aiming = true;
        ball->drag_start.x = ball->position.x;
        ball->drag_current.x = input_x;
        ball->drag_current.y = input_y;
    }
}

void Ball_OnPointerMove(Ball* ball, float input_x, float input_y) {
    if (!ball->is_aiming) return;

    ball->drag_current.x = input_x;
    ball->drag_current.y = input_y;
}

void Ball_OnPointerUp(Ball* ball) {
    if (!ball->is_aiming) return;

    // Pulling backwards to shoot forward:
    // Direction = (drag_start - drag_current)
    float pull_x = ball->drag_start.x - ball->drag_current.x;
    float pull_y = ball->drag_start.y - ball->drag_current.y;
    float pull_dist = sqrtf(pull_x * pull_x + pull_y * pull_y);

    if (pull_dist > 0.001f) {
        // Clamp pull distance to maximum allowed power
        if (pull_dist > ball->max_pull_distance) {
            pull_x = (pull_x / pull_dist) * ball->max_pull_distance;
            pull_y = (pull_y / pull_dist) * ball->max_pull_distance;
            pull_dist = ball->max_pull_distance;
        }

        // Apply launch velocity
        ball->velocity.x = pull_x * ball->power_multiplier;
        ball->velocity.y = pull_y * ball->power_multiplier;
    }

    ball->is_aiming = false;
}

void Ball_Update(Ball* ball, float delta_time) {
    // 1. Move ball based on current velocity
    ball->position.x += ball->velocity.x * delta_time;
    ball->position.y += ball->velocity.y * delta_time;

    // 2. Apply ground friction (exponential decay per second)
    float friction_factor = powf(ball->friction, delta_time * 60.0f);
    ball->velocity.x *= friction_factor;
    ball->velocity.y *= friction_factor;

    // 3. Complete stop threshold check
    float speed = sqrtf(ball->velocity.x * ball->velocity.x +
        ball->velocity.y * ball->velocity.y);
    if (speed < ball->min_stop_speed) {
        ball->velocity.x = 0.0f;
        ball->velocity.y = 0.0f;
    }
}

bool Ball_IsMoving(const Ball* ball) {
    return (ball->velocity.x != 0.0f || ball->velocity.y != 0.0f);
}

bool Ball_IsAiming(const Ball* ball) {
    return ball->is_aiming;
}