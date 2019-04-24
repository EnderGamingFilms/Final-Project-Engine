#include "Init.h"

EnemyExplode::EnemyExplode(float xPos, float yPos, float len)
{
	this->timer = ENEMY_EXPLODE_TIMER;
	this->midOffset = 0;

	Shader *localColor = this->getShader();
	localColor->Create("u_Color");
	localColor->setRgb(0.9, 0.3, 0);
	localColor->Use();
	localColor->UpdateUniform();
	localColor->unBind();

	float xVal = 0;
	this->length = len;
	this->midpoint[0] = xPos;
	this->midpoint[1] = yPos;
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
	{
		xVal = (float)i / 100;
		this->curve[i] = -0.4071 * pow(xVal, 3) + 0.3011 * pow(xVal, 2) + 0.0781 * xVal;
		this->curve[i] *= length;
		if (this->curve[i] < 0)
			this->curve[i] = 0;
	}
}

void EnemyExplode::Draw()
{
	this->getShader()->Use();
	
	float localX[CURVE_POINT_COUNT] = { 0 }, localY[CURVE_POINT_COUNT] = { 0 };
	float tempX, tempY;
	for (int i = 0; i < CURVE_POINT_COUNT; i++) //Initialize for first quadrant (rotate 45 deg ccw)
	{
		tempX = this->length * i / CURVE_POINT_COUNT + midOffset;
		tempY = this->curve[i];
		localX[i] = tempX * cos(PI / 4) - tempY * sin(PI / 4);
		localY[i] = tempY * cos(PI / 4) + tempX * sin(PI / 4);

	}
	glBegin(GL_POLYGON); //Q1
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localX[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localY[i] + this->midpoint[1]);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localY[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localX[i] + this->midpoint[1]);
	glEnd();


	for (int i = 0; i < CURVE_POINT_COUNT; i++) //Rotate 90 deg ccw to quadrant 2
		localX[i] = localX[i] * -1;
	glBegin(GL_POLYGON); //Q2
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localX[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localY[i] + this->midpoint[1]);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localY[i] * - 1 + this->midpoint[0]) * SQ_ASPECT_RATIO, localX[i] * -1 + this->midpoint[1]);
	glEnd();


	for (int i = 0; i < CURVE_POINT_COUNT; i++) //Rotate 90 deg ccw to quadrant 3
		localY[i] = localY[i] * -1;
	glBegin(GL_POLYGON); //Q3
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localX[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localY[i] + this->midpoint[1]);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localY[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localX[i] + this->midpoint[1]);
	glEnd();


	for (int i = 0; i < CURVE_POINT_COUNT; i++) //Rotate 90 deg ccw to quadrant 4
		localX[i] = localX[i] * -1;
	glBegin(GL_POLYGON); //Q4
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localX[i] + this->midpoint[0]) * SQ_ASPECT_RATIO, localY[i] + this->midpoint[1]);
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < CURVE_POINT_COUNT && (i <= 1 || this->curve[i - 1] != 0); i++)
		glVertex2f((localY[i] * -1 + this->midpoint[0]) * SQ_ASPECT_RATIO, localX[i] * -1 + this->midpoint[1]);
	glEnd();

	this->getShader()->unBind();
}

int EnemyExplode::iterate()
{
	if (this->timer <= 0)
		return FALSE_ITERATE;
	else
	{
		//int inflection = getMaxIndex(curve);
		this->Draw();
		
		this->timer--;
		this->length -= this->length / (2 * ENEMY_EXPLODE_TIMER); //Decreases length
		this->midOffset += this->length / (ENEMY_EXPLODE_TIMER); //Increases distance from midpoint
		if (timer < ENEMY_EXPLODE_TIMER *  3/4) //Doesn't swell until 1/4 of animation performed
		{
			this->getShader()->fade(ENEMY_EXPLODE_TIMER);
			for (int i = 0; i < CURVE_POINT_COUNT; i++)
			{
				if (this->curve[i] < this->length / 4) //Prevents values from overgrowing from exponetial growth
					this->curve[i] += this->curve[i] * this->curve[i] * ENEMY_EXPLODE_TIMER * SWELL_CONSTANT;
				/*if (i > inflection)
					this->curve[i] += pow(inflection - i, 2) * this->curve[i] / (float)(ENEMY_EXPLODE_TIMER * CURVE_POINT_COUNT);*/
				//Above used if end of curve is not magnified enough - at default length and timer of 60 currently not necessary
			}
		}
		return this->timer;
	}
}

int EnemyExplode::getTimer()
{
	return this->timer;
}

int getMaxIndex(float *arr)
{
	float max = 0;
	int maxInd = 0;
	for (int i = 0; i < CURVE_POINT_COUNT; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			maxInd = i;
		}
	}
	return maxInd;
}