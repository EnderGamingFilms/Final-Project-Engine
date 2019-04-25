#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class Enemy : public Triangle
{
public:
	Enemy() { return; }

	Enemy(float xSpeed, float ySpeed, float rotateSpeed, float size);

	void Init(float xSpeed, float ySpeed, float rotateSpeed, float size);

	float getMoveX() { return moveX; }
	float getMoveY() { return moveY; }
	float getMoveRotate() { return moveRotate; }

	void swapMX() { moveX = moveX * -1; }
	void swapMY() { moveY = moveY * -1; }

private:

	float moveX;

	float moveY;

	float moveRotate;
};


class Swarm
{
public:
	Swarm(float xSpeed, float ySpeed, float rotateSpeed, float size, unsigned int colorID);

	void Spawn(float x, float y);

	void Spawn(float x, float y, int seconds, long int vsynccounter);

	bool Kill(int index);

	void getMids(int index, float m[2]);

	void Ping();

	int checkForDamage(Hitbox &h);

	//returns the hitbox if alive, otherwise nullptr
	Hitbox * getHitBox(int index);

private:
	float size;

	Enemy swarm[16];
	Hitbox sbox[16];
	bool alive[16];

	int numAlive;

	Bounds gameBounds;

	unsigned int color;
};