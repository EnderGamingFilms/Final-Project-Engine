#define GLEW_STATIC

#define RELEASE_MODE false

#define SQ_ASPECT_RATIO 0.5625

#define SQ_RATIO_RECIP 1.777777778

#define USE_X_Y_ASPECT_RATIO true

#define _CRT_SECURE_NO_WARNINGS

#define NO_CHANGE 2

#define PI 3.1415926

#define ROUND_TO_ZERO 0.0000001

#define MAGAZINE_SIZE 30

#define ENEMY_SIZE 0.11

#define FIRE_RATE 8

#define FALSE_ITERATE -1

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Hitbox.h"
#include "HitArray.h"
#include "Bounds.h"
#include "Circle.h"
#include "TestClass.h"
#include "GraphicNumber.h"
#include "ScoreBoard.h"
#include "Ship.h"
#include "Bullet.h"
#include "Swarm.h"
#include "Magazine.h"
#include "FireTimer.h"

using std::string;
using std::fstream;
using std::getline;
using std::stringstream;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::queue;

unsigned int CompileShader(unsigned int type, const string & source);

unsigned int CreateShadervf(const string & vertexShader, const string & fragmentShader);

void printGameMenu(const string &name);

int getMenuOption(int menuMin, int menuMax, void menu(const string &name), const string &name);

//type of data enum
enum dataType{fourF, oneI};

enum direction{south, west, north, east};


class Shader
{
public:
	~Shader();

	Shader() { return; }

	Shader(const string &InitFile, dataType u_Type, int textureSlot = 0);

	void Init(const string &InitFile, dataType u_Type, int textureSlot);

	void Create(const char *locationKey);

	unsigned int ID();

	int Location();

	void Use();

	void UpdateUniform();

	void setRgb(float r, float g, float b);

	void setTextureSlot(int &slot) { this->textureSlot = slot; }

	void unBind();

	string getVertexString();
	string getFragmentString();

	void fade(float timer);

private:

	int loc;

	unsigned int shaderID;

	string sVertex;

	string sFragment;

	dataType U_Type;

	float rgb[3];

	int textureSlot;
};


class gameWindow
{
public:
	gameWindow();
	gameWindow(int width, const char *windowName);

	void Create(int width, const char *windowName);

	void makeCoreProfile(int versionMajor = 3, int versionMinor = 3);

	bool validateWindow();

	void makeCurrentContext();

	void vSync(bool tf);

	void Clear() { glClear(GL_COLOR_BUFFER_BIT); }

	GLFWwindow * get();

	int getWidth() { return width; }
	int getHeight() { return height; }

private:
	GLFWwindow *window;
	int width;
	int height;
};

