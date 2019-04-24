#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class graphicNumber
{
public:
	graphicNumber();

	void init(float size);

	void insert(int n, int digits);

	bool isEmptyNum();

	void Draw();

	void clearMap();

	void transLate(float x, float y);

	bool incr();

	Hitbox * getSquareAtIndex(int i, int j);

	void midNum(float mids[2]);

protected:

	bool isEmpty;

	int number;
	int numDigits;
	float width;
	float bitWidth;

	int numBits;
	Hitbox squares[8][8];

	bool map[8][8];
};
