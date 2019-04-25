#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>
#include "Shader.h"

#define CURVE_POINT_COUNT 99
#define PI 3.14159
#define ENEMY_EXPLODE_TIMER 60
#define SWELL_CONSTANT 0.1

class EnemyExplode : public Shape
{
public:
	EnemyExplode(float xPos = 0, float yPos = 0, float len = 0.05);
	void Draw();
	int iterate(); //True for continue iterating, false for finished -> delete object
	int getTimer();
private:
	float midpoint[2];
	float curve[CURVE_POINT_COUNT];
	float length;
	float midOffset; //Distance start point is from the center

	int timer; //When it reaches 0, 


};

int getMaxIndex(float *arr);