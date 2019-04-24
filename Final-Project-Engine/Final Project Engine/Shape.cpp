#include "Init.h"

Shape::Shape()
{
	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = 0;
	this->sizeofDataTypeInBytes = 0;
	this->numFloats = 0;
	this->matrix = nullptr;
	this->isIndexed = false;
	this->numIndeces = 0;
	this->indeces = nullptr;
	this->vertexStride = 0;
	this->drawType = GL_DYNAMIC_DRAW;
	this->bufferType = GL_ARRAY_BUFFER;
	this->indexBufferType = GL_ELEMENT_ARRAY_BUFFER;
	this->componentsPerVertex = 0;
	this->isAlloced = false;

	this->color = new Shader();
}

Shape::~Shape() 
{
	if (isAlloced)
	{
		delete[]matrix;

		if (isIndexed)
		{
			delete[]indeces;
		}
	}
}

int Shape::iterate()
{
	cout << "ierate" << endl;
	return -1;
}

Shader * Shape::getShader()
{
	return this->color;
}

void Shape::Init(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes, int numFloats, float newMatix[], bool isIndexed, int numIndeces, unsigned int newIndeces[],
int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType)
{
	float aspectRatio = 1.0f;

	if (USE_X_Y_ASPECT_RATIO == true)
	{
		aspectRatio = SQ_ASPECT_RATIO;
	}


	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = numVerteces;
	this->sizeofDataTypeInBytes = sizeofDataTypeBytes;
	this->numFloats = numFloats;
	this->matrix = nullptr;
	this->isIndexed = isIndexed;
	this->numIndeces = numIndeces;

	if (!isIndexed)
		this->indeces = nullptr;

	this->vertexStride = vertexStride;
	this->drawType = drawType;
	this->bufferType = bufferType;
	this->indexBufferType = indexBufferType;
	this->componentsPerVertex = componentsPerVertex;

	matrix = new float[numFloats];

	for (int i = 2, j = 0; i < numFloats + 2; i++, j++)
	{
		if (i % 2 == 0) //if x
			matrix[j] = (newMatix[j] * aspectRatio);
		else
			matrix[j] = newMatix[j];
	}

	if (isIndexed == true)
	{
		indeces = new unsigned int[numIndeces];

		for (int i = 0; i < numIndeces; i++)
		{
			indeces[i] = newIndeces[i];
		}
	}

	this->isAlloced = true;


	glGenVertexArrays(1, &vertexArrayObject); //creating a vertex array (required when using core mode or publishing) and binding, nothing is actually done with it
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(bufferType, vertexBuffer);

	glBufferData(bufferType, sizeofDataTypeBytes * numFloats, matrix, drawType);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeBytes * vertexStride, 0); //this is the line of code which links the buffer (at index 0 (function paramater 1)) to the vertex array object

	if (isIndexed == true)
	{
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(indexBufferType, indexBuffer); //GL_ELEMENT_ARRAY_BUFFER for an index buffer
		glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
	}
}


Shape::Shape(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes, int numFloats, float newMatix[], bool isIndexed, 
	int numIndeces, unsigned int newIndeces[], int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType)
{

	float aspectRatio = 1.0f;

	if (USE_X_Y_ASPECT_RATIO == true)
	{
		aspectRatio = SQ_ASPECT_RATIO;
	}


	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->numVerteces = numVerteces;
	this->sizeofDataTypeInBytes = sizeofDataTypeBytes;
	this->numFloats = numFloats;
	this->matrix = nullptr;
	this->isIndexed = isIndexed;
	this->numIndeces = numIndeces;

	if(!isIndexed)
	this->indeces = nullptr;

	this->vertexStride = vertexStride;
	this->drawType = drawType;
	this->bufferType = bufferType;
	this->indexBufferType = indexBufferType;
	this->componentsPerVertex = componentsPerVertex;

	matrix = new float[numFloats];

	for (int i = 2, j = 0; i < numFloats + 2; i++, j++)
	{
		if (i % 2 == 0) //if x
			matrix[j] = (newMatix[j] * aspectRatio);
		else
			matrix[j] = newMatix[j];
	}

	if (isIndexed == true)
	{
		indeces = new unsigned int[numIndeces];

		for (int i = 0; i < numIndeces; i++)
		{
			indeces[i] = newIndeces[i];		
		}
	}

	this->isAlloced = true;


	glGenVertexArrays(1, &vertexArrayObject); //creating a vertex array (required when using core mode or publishing) and binding, nothing is actually done with it
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(bufferType, vertexBuffer);

	glBufferData(bufferType, sizeofDataTypeBytes * numFloats, matrix, drawType);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeBytes * vertexStride, 0);

	if (isIndexed == true)
	{
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(indexBufferType, indexBuffer);
		glBufferData(indexBufferType, sizeof(unsigned int) * numIndeces, indeces, drawType);
	}

}


void Shape::Draw()
{
	if (isAlloced)
	{
		if (isIndexed)
		{
			glDrawElements(GL_TRIANGLES, getNumIndeces(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, getNumVerteces());
		}
	}
	else
	{
		cout << "isAlloced was false: Attempted to draw a shape which hasnt been buffered yet!" << endl;
	}
}



void Shape::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Shape::BufferVertex()
{
	if (isAlloced)
	{
		glBufferData(bufferType, sizeofDataTypeInBytes * numFloats, matrix, drawType);
	}
}


void Shape::Bind()
{
	if (isAlloced)
	{
		glBindBuffer(bufferType, vertexBuffer);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, sizeofDataTypeInBytes * vertexStride, 0);

		glBindVertexArray(vertexArrayObject);

		if(isIndexed)
		glBindBuffer(indexBufferType, indexBuffer);
	}
	else
	{
		cout << "isAlloced was false: Attempted to bind a shape which hasnt been allocated yet" << endl;
	}
}
