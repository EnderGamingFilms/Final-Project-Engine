#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <time.h>

using std::string;

enum dataType { fourF, oneI };

class Shader
{
public:
	~Shader();

	Shader(const string &InitFile = "basic.shader", dataType u_Type = fourF, int textureSlot = 0);

	void Create(const char *locationKey);

	unsigned int ID();

	int Location();

	void Use();

	void UpdateUniform();

	void setRgb(float r, float g, float b);

	void setTextureSlot(int &slot) { this->textureSlot = slot; }

	void unBind();

	void fade(float timer);

	string getVertexString();
	string getFragmentString();

private:

	int loc;

	unsigned int shaderID;

	string sVertex;

	string sFragment;

	dataType U_Type;

	float rgb[3];

	int textureSlot;
};
