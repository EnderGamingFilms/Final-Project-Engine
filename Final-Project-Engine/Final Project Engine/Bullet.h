#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


class Bullet : public Hitbox , public Circle
{
public:
	~Bullet() { this->isInitialized = false; return; }

	Bullet() { return; }

	Bullet(float xSpawn, float ySpawn, float size, float speed, float fireAngle);

	bool getIsInit() { return this->isInitialized; }

	void Init(float xSpawn, float ySpawn, float size, float speed, float fireAngle);

	void Draw();

	void Fly();

	void Reset();

private:
	float speed;
	float size;

	float firedAngle;

	bool isInitialized;
};