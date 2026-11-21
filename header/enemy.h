#pragma once
#include "cprocessing.h"
#include "header/level.h"
#include "header/constants.h"
#include "header/ball.h"

//idk if need yet la can see when i do logic
typedef struct {
    CP_Vector position;
    CP_Vector velocity;
    float speed;
    float radius;
} Enemy;

void Enemy_Init(Enemy* enemy, CP_Vector position);
void Draw_Enemy(CP_Image img, CP_Vector position);
void Enemy_Chase(Enemy* enemy, Ball* ball, float dt);