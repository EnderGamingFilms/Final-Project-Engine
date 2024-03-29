#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

/*
	Hitbox Notes:

	-If an object using hitboxes is resized its hitboxes must be resized
	
	-If and object using hitboxes is swung or rotated its hitboxes must be swung or rotated

*/

class Hitbox : public Rectangle
{
public:
	Hitbox() { return; }

	/* Constructs a square hitbox of the given height and width*/
	Hitbox(float size);

	/* Initializes a square hitbox */
	void Init(float size);

	/* Returns true if the this hitbox in any way overlaps the checkBox */
	bool isOverlap(Hitbox &checkBox);

	/* Returns the hitboxes checkPoint (should be midpoint) */
	void checkPoint(float m[2]) { Rectangle::CalcMidPoint(m);}

	/* returns the hitboxes halfwidth */
	float getHalf() { return this->half; }

private:
	float size;
	float half;
};