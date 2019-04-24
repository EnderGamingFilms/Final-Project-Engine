#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class ScoreBoard
{
public:
	ScoreBoard(int numDigits, float sizeNums, float tX, float tY, float numberSpacing);

	void incr();

	void Draw();

	long int getRealNum() { return this->realNum; }

private:
	graphicNumber * board;
	long int realNum;
	int numDigits;

	int base;
};
