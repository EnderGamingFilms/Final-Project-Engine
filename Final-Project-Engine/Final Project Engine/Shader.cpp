#include "Init.h"

Shader::Shader(const string &InitFile, dataType u_Type, int textureSlot)
{
	string temp;
	stringstream vertexString;
	stringstream fragmentString;

	this->U_Type = u_Type;
	this->textureSlot = textureSlot;

	for (int i = 0; i < 3; i++)
	{
		rgb[i] = 1.0f;
	}

	fstream infile;
	infile.open(InitFile);

	if (!infile.is_open())
	{
		std::cout << "Error opening file " << InitFile << std::endl;
	}

	enum ShaderType
	{
		none, vertex, frag
	};

	ShaderType currentType = none;

	while (getline(infile, temp))
	{
		if (temp.find("#shader") != string::npos)
		{
			if (temp.find("vertex") != string::npos)
			{
				currentType = vertex;
			}
			else if (temp.find("fragment") != string::npos)
			{
				currentType = frag;
			}
			else
			{
				std::cout << "#shader define found with invalid type in ParseFile" << std::endl;
			}
		}
		else
		{
			switch (currentType)
			{
			case vertex:
				vertexString << temp << '\n';
				break;
			case frag:
				fragmentString << temp << '\n';
				break;
			default:
				break;
			}
		}
	}

	infile.close();

	this->sVertex = vertexString.str();
	this->sFragment = fragmentString.str();
}

void Shader::setRgb(float r, float g, float b)
{
	if (r != NO_CHANGE)
		rgb[0] = r;

	if (g != NO_CHANGE)
		rgb[1] = g;

	if (b != NO_CHANGE)
		rgb[2] = b;
}

int Shader::Location()
{
	return this->loc;
}

unsigned int Shader::ID()
{
	return this->shaderID;
}


void Shader::Create(const char *locationKey)
{
	unsigned int temp = CreateShadervf(sVertex, sFragment);

	int location = 0;

	location = glGetUniformLocation(temp, locationKey);

	this->loc = location;
	this->shaderID = temp;
}

void Shader::Use()
{
	glUseProgram(shaderID);
}


void Shader::UpdateUniform()
{
	//the uniform name that we created the location out of must match! (u_Color or u_Texture)

	switch (this->U_Type)
	{
	case fourF:
		glUniform4f(loc, rgb[0], rgb[1], rgb[2], 1.0f);
		break;
	case oneI:
		glUniform1i(loc, textureSlot);
		break;
	default:
		cout << "Update Uniform enum Datatype Not Recognized" << endl;
	}
}


Shader::~Shader()
{
	glDeleteProgram(this->shaderID);
}

string Shader::getVertexString()
{
	return this->sVertex;
}

string Shader::getFragmentString()
{
	return this->sFragment;
}

void Shader::unBind()
{
	glUseProgram(0);
}

void Shader::fade(float timer)
{
	float mult = timer / (timer + 5); //Approaches 0 as timer approaches 0, approaches 1 as timer approaches infinty
	this->rgb[0] *= mult;
	this->rgb[1] *= mult;
	this->rgb[2] *= mult;
	this->Use();
	this->UpdateUniform();
}
