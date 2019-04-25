#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

class TestClass
{
public:

	int HitBoxTranslations();

	int Scoreboard();

	int KeepTriangleInbounds();

	/* Use a FreeRotate function which does not update the objects current rotation to initialize, along with hitarray etc*/

	int FreeMovements();

	int HitAnimation();


private:

	void Notify() {	std::cout << "********************************" << std::endl <<  "Test Function Entered" << std::endl << "********************************" << std::endl; }

};
