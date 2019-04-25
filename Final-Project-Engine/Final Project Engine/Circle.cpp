#include "Init.h"

Circle::Circle(float r, float xPos, float yPos)
{
	this->radius = r;
	this->midpoint[0] = xPos;
	this->midpoint[1] = yPos;
}

void Circle::Init(float r, float xPos, float yPos)
{
	this->radius = r;
	this->midpoint[0] = xPos;
	this->midpoint[1] = yPos;
}

void Circle::getMidpoint(float mid[2])
{
	mid[0] = this->midpoint[0];
	mid[1] = this->midpoint[1];
}

float Circle::getX()
{
	return this->midpoint[0];
}

float Circle::getY()
{
	return this->midpoint[1];
}

float Circle::getRadius()
{
	return this->radius;
}

void Circle::Draw()
{
	glBegin(GL_POLYGON); //Starts the "loop" which will become the circle

	for (int deg = 0; deg < CIRCLE_SIDES; deg++) //Define points along the circle's circumfrence - number of points is equal to CIRCLE_SIDES
	{
		float radians = deg * PI / 180; //Converts degrees to radians
		glVertex2f((cos(radians)*this->radius + midpoint[0]) * SQ_ASPECT_RATIO, sin(radians)*this->radius + midpoint[1]); //Adds a vertex to the glBegin

	}
	glEnd(); //Finishes and closes loop
}

void Circle::Translate(float xAmount, float yAmount)
{
	/* why do we have to use the reciprocal when we translate? is it build in to the gl functions*/

	midpoint[0] += xAmount / SQ_ASPECT_RATIO; //Modifies x pos
	midpoint[1] += yAmount; //Modifies y pos
}

void Circle::TranslateToOrigin()
{
	float mids[2];
	getMidpoint(mids);

	float xTranslation = mids[0] * -1;
	float yTranslation = mids[1] * -1;

	Translate(xTranslation, yTranslation);
}

void Circle::Swing(float theta)
{
	float tempX, tempY;
	tempX = midpoint[0] / SQ_ASPECT_RATIO; //Scale x axis down
	tempY = midpoint[1] / SQ_ASPECT_RATIO; //Scale y axis down

	midpoint[0] = tempX * cos(theta) - tempY * sin(theta);
	midpoint[1] = tempY * cos(theta) + tempX * sin(theta);
	midpoint[0] *= SQ_ASPECT_RATIO; //Scale x axis up
	midpoint[1] *= SQ_ASPECT_RATIO; //Scale y axis up
}