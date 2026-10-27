#include <math.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "header/ball.h"
#include "header/draw.h"

void Ball_Init(Ball* ball, CP_Vector position, float radius) {
    ball->position = position;
    ball->velocity = CP_Vector_Set(0.0f, 0.0f);
    ball->radius = radius;

    ball->is_aiming = false;
    ball->drag_start = CP_Vector_Set(0.0f, 0.0f);
    ball->drag_current = CP_Vector_Set(0.0f, 0.0f);

    // Ground resistance & mechanics tuning
    ball->friction = 0.92f;   // Lower for rough grass, higher for slick greens
    ball->min_stop_speed = 1.5f;    // Below this speed, the ball stops completely
    ball->power_multiplier = 5.0f;    // Shot power scaling factor
    ball->max_pull_distance = 240.0f;  // Max drag reach
}

void Ball_OnPointerDown(Ball* ball, CP_Vector position) {
    // Only allow initiating a shot if the ball is completely stationary
    if (Ball_IsMoving(ball)) {
        return;
    }

    // Check if the click is close to the ball
    float dist = CP_Vector_Length(CP_Vector_Subtract(position, ball->position));

    if (dist <= ball->radius * 2.0f) {
        ball->is_aiming = true;
        ball->drag_start = ball->position;
        ball->drag_current = position;
    }
}

void Ball_OnPointerMove(Ball* ball, CP_Vector position) {
    if (!ball->is_aiming) return;

    ball->drag_current = position;
}

void Ball_OnPointerUp(Ball* ball) {
    if (!ball->is_aiming) return;

    // Pulling backwards to shoot forward: pull = drag_start - drag_current
    CP_Vector pull = CP_Vector_Subtract(ball->drag_start, ball->drag_current);
    float pull_dist = CP_Vector_Length(pull);

    if (pull_dist > 0.001f) {
        // Clamp pull length to the maximum allowed power
        if (pull_dist > ball->max_pull_distance) {
            pull = CP_Vector_Scale(pull, ball->max_pull_distance / pull_dist);
        }

        // Apply launch velocity
        ball->velocity = CP_Vector_Scale(pull, ball->power_multiplier);
    }

    ball->is_aiming = false;
}

// Clamped pull vector(points in the launch direction). (0, 0) when not aiming.
// Used by both the shot and the aim line so they always agree.
CP_Vector Ball_GetPull(const Ball * ball) {
    if (!ball->is_aiming) return CP_Vector_Set(0.0f, 0.0f);

    CP_Vector pull = CP_Vector_Subtract(ball->drag_start, ball->drag_current);
    float len = CP_Vector_Length(pull);

    if (len > ball->max_pull_distance) {
        pull = CP_Vector_Scale(pull, ball->max_pull_distance / len);
    }
    return pull;
}

// Dotted aim line, drawn while dragging
void Ball_DrawAim(const Ball* ball) {
    CP_Vector pull = Ball_GetPull(ball);
    if (CP_Vector_Length(pull) <= 0.001f) return;

    CP_Vector end = CP_Vector_Add(ball->position, pull);
    draw_dotted_line(ball->position.x, ball->position.y,
        end.x, end.y,
        14.0f, 6.0f, CP_Color_Create(255, 255, 255, 200));
}

// Draw the horse sprite as the player
void Draw_Player(CP_Image img, CP_Vector position, float img_width, float img_height) {
    draw_image(img, position.x, position.y, img_width, img_height, 255);
}

void Ball_Update(Ball* ball, float delta_time) {
    // 1. Move ball based on current velocity
    ball->position = CP_Vector_Add(ball->position,
        CP_Vector_Scale(ball->velocity, delta_time));

    // 2. Apply ground friction (exponential decay per second)
    float friction_factor = powf(ball->friction, delta_time * 60.0f);
    ball->velocity = CP_Vector_Scale(ball->velocity, friction_factor);

    // 3. Complete stop threshold check
    if (CP_Vector_Length(ball->velocity) < ball->min_stop_speed) {
        ball->velocity = CP_Vector_Set(0.0f, 0.0f);
    }
}

bool Ball_IsMoving(const Ball* ball) {
    return (ball->velocity.x != 0.0f || ball->velocity.y != 0.0f);
}

bool Ball_IsAiming(const Ball* ball) {
    return ball->is_aiming;
}