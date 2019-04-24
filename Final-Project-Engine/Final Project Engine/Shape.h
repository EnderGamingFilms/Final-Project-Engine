#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "Shader.h"




/* Notes For Derriving*/

/*
	- Derrived classes must have a calcMidpoint() function

	- Coordinate type is assumed as float, but still can be passed in to account for differences in sizeof() operators

	- Index type is assumed as unsigned int

	- When using matrix[] x and y coordinates in implicit equations (trigonometric operations) you must dereference x by (x * SQ_RATIO_RECIP) [do operation] then rereference (x * SQ_ASPECT_RATIO) then bind()

*/


class Shape
{
public:

	/*Contructor*/

	virtual ~Shape();

	Shape();

	Shape(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

		int numFloats, float newMatix[],

		bool isIndexed, int numIndeces, unsigned int newIndeces[],

		int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType);


	void Init(int numVerteces, int componentsPerVertex, int sizeofDataTypeBytes,

		int numFloats, float newMatix[],

		bool isIndexed, int numIndeces, unsigned int newIndeces[],

		int vertexStride, GLenum drawType, GLenum bufferType, GLenum indexBufferType);


	/*Getters*/

	int getComponentsPerVertex() { return this->componentsPerVertex; }
	unsigned int getVertexBuff() { return this->vertexBuffer; }
	unsigned int getIndexBuff() { return this->indexBuffer; }

	int getNumVerteces() { return this->numVerteces; }
	int getSizeOfDataBytes() { return this->sizeofDataTypeInBytes; }

	int getNumFloats() { return this->numFloats; }
	float * getMatrix() { return matrix; }

	int getVertexStride() { return this->vertexStride; }

	bool getIsIndexed() { return this->isIndexed; }
	int getNumIndeces() { return this->numIndeces; }
	unsigned int * getIndeces() { return indeces; }

	GLenum getDrawType() { return this->drawType; }
	GLenum getBufferType() { return this->bufferType; }
	GLenum getIndexBufferType() { return this->indexBufferType; }

	bool getIsAlloced() { return isAlloced; }

	void isAllocedBypass() { isAlloced = true; std::cout << "IsAlloced was bypassed, VBO ID: " << vertexBuffer << std::endl; }

	/*Operations*/

	void Unbind();

	void Bind();

	void BufferVertex();

	/*Virtual Operations*/

	virtual void Draw();

	virtual void TranslateToOrigin() { return; }

	virtual void Translate(float, float) { return; }

	virtual void Rotate(float) { return; }

	virtual void Swing(float) { return; }

	virtual void CalcMidpoint(float[2]) { return; }

	virtual int iterate();

	Shader * getShader();

private:

	/*Buffers*/

	unsigned int vertexBuffer;
	unsigned int indexBuffer;

	/*Members*/

	int componentsPerVertex;
	int numVerteces;
	int sizeofDataTypeInBytes;

	int numFloats;
	float *matrix;

	int vertexStride;

	bool isIndexed;
	int numIndeces;
	unsigned int *indeces;

	GLenum drawType;
	GLenum bufferType;
	GLenum indexBufferType;

	unsigned int vertexArrayObject; // (dont have to use)

	bool isAlloced;

	Shader * color;
};