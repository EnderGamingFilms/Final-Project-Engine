#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class Ship
{
public:
	Ship(float turnSpeed, float movementSpeed, unsigned int bodyColor, unsigned int rivetColor);

	void Draw();

	void Translate(float x, float y);

	void Rotate(float theta);

	void Swing(float theta);

	void FreeRotate(float theta);

	void FreeSwing(float theta);

	void UserMove(GLFWwindow * window);

	float getCurrentRotation();

	void Bounce(float bounce);

	float getSpeed() { return movementSpeed; }

	bool isFired(GLFWwindow * win);

	void CalcApproxMidPoint(float m[2]);

	Hitbox * getHitbox();


private:

	Bounds gameBound;
	Boundlimit lim;

	/*Rendering*/
	Triangle body;
	Rectangle leftRivet;
	Rectangle rightRivet;
	Circle thruster;

	/*Hitbox*/
	Hitbox hb;

	/*Attributes*/
	float turnSpeed;
	float movementSpeed;

	/*Shad*/
	unsigned int bodyColor;
	unsigned int rivetColor;

	bool isAlloced;
};