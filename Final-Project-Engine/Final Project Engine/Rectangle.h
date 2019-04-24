#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


class Rectangle : virtual public Shape
{
public:
	Rectangle() { return; }

	Rectangle(float height, float width);

	void Init(float height, float width);

	float getWidth() { return this->width; }
	float getHeight() { return this->height; }
	float getCurrentRotation() { return this->currentRotation; }

	void CalcMidPoint(float mids[2]);

	void EditVertex(unsigned int vertex, float xOffset, float yOffset);

	void Resize(float factor);

	void TranslateToOrigin();

	virtual void Translate(float xAmount, float yAmount);

	void Swing(float theta);

	void Rotate(float theta);

	void FreeSwing(float theta);

	void FreeRotate(float theta);

private:

	float *newMatrix;
	unsigned int *newInd;

	float height;
	float width;

	float currentRotation;
	
};