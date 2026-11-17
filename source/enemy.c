// Libraries
#include "cprocessing.h"
#include "header/draw.h"
#include "header/enemy.h"
#include "header/ball.h"

void Draw_Enemy(CP_Image img, CP_Vector position, float img_width, float img_height) {
	draw_image(img, position.x, position.y, img_width, img_height, 255);
}

void Enemy_Init(Enemy* enemy, CP_Vector position) {
	enemy->position = position;
	enemy->velocity = CP_Vector_Set(0.0f, 0.0f);
	enemy->radius = ENEMY_RADIUS;
	enemy->speed = ENEMY_SPEED;
}

void Enemy_Chase(Enemy* enemy, Ball* ball, float dt) {
	CP_Vector toBall = CP_Vector_Subtract(ball->position, enemy->position);
	if (CP_Vector_Length(toBall) < 0.001f)	return;

	CP_Vector direction = CP_Vector_Normalize(toBall);
	enemy->velocity = CP_Vector_Scale(direction, enemy->speed);
	enemy->position = CP_Vector_Add((*enemy).position, CP_Vector_Scale((*enemy).velocity, dt));
}