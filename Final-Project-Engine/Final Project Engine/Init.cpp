#include "Init.h"

void printGameMenu(const string & name)
{
	system("cls");
	cout << " ------- Welcome To " << name << "! ------- " << endl;
	cout << "1) Play Game" << endl;
	cout << "2) Tutorial" << endl << endl;
	cout << "3) Exit" << endl;

}

int getMenuOption(int menuMin, int menuMax, void menu(const string &name), const string &name)
{
	int option = -1;

	while (option < menuMin || option > menuMax)
	{
		system("cls");
		menu(name);
		cin >> option;
	}

	return option;
}


void Shader::Init(const string &InitFile, dataType u_Type, int textureSlot)
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

void Shader::unBind()
{
	glUseProgram(0);
}

void Shader::setRgb(float r, float g, float b)
{
	if(r != NO_CHANGE)
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


void Shader::fade(float timer)
{
	float mult = timer / (timer + 5); //Approaches 0 as timer approaches 0, approaches 1 as timer approaches infinty
	this->rgb[0] *= mult;
	this->rgb[1] *= mult;
	this->rgb[2] *= mult;
	this->Use();
	this->UpdateUniform();
}

string Shader::getVertexString()
{
	return this->sVertex;
}

string Shader::getFragmentString()
{
	return this->sFragment;
}

gameWindow::gameWindow()
{
	this->window = nullptr;
}

gameWindow::gameWindow(int width, const char *windowName)
{
	window = glfwCreateWindow(width, width * SQ_ASPECT_RATIO, windowName, NULL, NULL);
	this->width = width;
	this->height = width * SQ_ASPECT_RATIO;
}

void gameWindow::Create(int width, const char *windowName)
{
	if (window == nullptr)
	{
		window = glfwCreateWindow(width, width * SQ_ASPECT_RATIO, windowName, NULL, NULL);
	}
	else
	{
		cout << "Window.Create() called but the window was already created!" << endl;
	}
}

void gameWindow::makeCoreProfile(int versionMajor, int versionMinor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool gameWindow::validateWindow()
{
	if (window == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void gameWindow::makeCurrentContext()
{
	glfwMakeContextCurrent(this->window);
}

void gameWindow::vSync(bool tf)
{
	switch (tf)
	{
	case true:
		glfwSwapInterval(1);
		break;
	case false:
		glfwSwapInterval(0);
		break;
	}

	return;
}

GLFWwindow * gameWindow::get()
{
	return this->window;
}


//NON MEMBER -----------------------------------------------------------------------------------------------------------------------------


unsigned int CompileShader(unsigned int type, const string & source)
{
	unsigned int id = glCreateShader(type);

	const char *src = &source[0];

	glShaderSource(id, 1, &src, nullptr);

	glCompileShader(id);

	//do: error handling here


	//ERROR CHECK
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;

}


unsigned int CreateShadervf(const string & vertexShader, const string & fragmentShader)
{
	unsigned int program = glCreateProgram();

	unsigned int vertexShad = CompileShader(GL_VERTEX_SHADER, vertexShader);
	//creating an id for the vertex shader (called per vertex)

	unsigned int fragmentShad = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	//creating an id for a fragment shader (called per pixel in the shape)

	glAttachShader(program, vertexShad);
	glAttachShader(program, fragmentShad);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShad);
	glDeleteShader(fragmentShad);
	//the shaders are linked to the program which has been created now, so now they can be freed

	return program;
}