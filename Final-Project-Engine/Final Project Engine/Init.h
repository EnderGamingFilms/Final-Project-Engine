#pragma once

#define GLEW_STATIC

#define RELEASE_MODE true

#define SQ_ASPECT_RATIO 0.5625

#define SQ_RATIO_RECIP 1.777777778

#define USE_X_Y_ASPECT_RATIO true

#define _CRT_SECURE_NO_WARNINGS

#define NO_CHANGE 2

#define PI 3.1415926

#define ROUND_TO_ZERO 0.0000001

#define ENEMY_SIZE 0.15


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
#include "Shader.h"
#include "Enemy.h"
#include "DestructorList.h"
#include "EnemyExplode.h"
#include "EnemyList.h"
#include "Node.h"
#include "List.h"
#include "BulletList.h"

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

//type of data enum

enum direction { south, west, north, east };


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

