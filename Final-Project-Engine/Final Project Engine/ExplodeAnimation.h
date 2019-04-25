#pragma once

#include "Init.h"

#define CURVE_POINT_COUNT 99
#define PI 3.14159
#define ENEMY_EXPLODE_TIMER 60
#define SWELL_CONSTANT 0.05

class EnemyExplode : public Shape
{
public:
	EnemyExplode() { return; }
	EnemyExplode(float xPos, float yPos, float len);
	void Init(float xPos = 0, float yPos = 0, float len = 0.1);
	void Draw();
	int iterate(); //True for continue iterating, false for finished -> delete object
	int getTimer();
private:
	float midpoint[2];
	float curve[CURVE_POINT_COUNT];
	float length;
	float midOffset; //Distance start point is from the center

	int timer; //When it reaches 0, 

	Shader shad;


};

int getMaxIndex(float *arr);