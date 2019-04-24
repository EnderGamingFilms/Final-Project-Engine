#include "Init.h"


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