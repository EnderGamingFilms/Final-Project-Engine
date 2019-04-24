#include "Init.h"

Hitbox::Hitbox(float size) 
{
	this->size = size;
	this->half = size / 2;

	Rectangle::Init(size, size);
}

void Hitbox::Init(float size)
{
	this->size = size;
	this->half = size / 2;

	Rectangle::Init(size, size);
}

bool Hitbox::isOverlap(Hitbox &checkBox)
{
	float m1[2] = { 0.0f };
	float m2[2] = { 0.0f };
	float zonePM = 0.0f;
	bool xMatch = false, yMatch = false;

	zonePM = (getHalf() + checkBox.getHalf()) / 2;

	checkPoint(m1);
	checkBox.checkPoint(m2);

	float x1 = m1[0];
	float x2 = m2[0];

	float y1 = m1[1];
	float y2 = m2[1];

	if (x1 > x2)
	{
		if (x1 - zonePM <= x2)
		{
			xMatch = true;
		}
	}
	else if (x2 > x1)
	{
		if (x2 - zonePM <= x1)
		{
			xMatch = true;
		}
	}
	else if(x1 == x2)
	{
		xMatch = true;
	}

	if (y1 > y2)
	{
		if (y1 - zonePM <= y2)
		{
			yMatch = true;
		}
	}
	else if (y2 > y1)
	{
		if (y2 - zonePM <= y1)
		{
			yMatch = true;
		}
	}
	else if (y1 == y2)
	{
		yMatch = true;
	}


	if (xMatch == true && yMatch == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}