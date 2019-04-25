#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


class Mag
{
public:
	Mag(float speed, float size, unsigned int colorID);

	void Shoot(float spawnX, float spawnY, float theta);

	void Ping();

	void DestoryBullet(int index);

	bool isContact(Hitbox &h);


private:
	Bounds gameBounds;

	Bullet buls[MAGAZINE_SIZE];
	bool InPlay[MAGAZINE_SIZE];

	float size;
	float speed;

	int numInPlay;

	unsigned int color;
};