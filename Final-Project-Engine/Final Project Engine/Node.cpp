#include "Init.h"

Node::Node(Shape *set)
{
	this->nextPtr = nullptr;
	this->data = set;
}

Shape * Node::getData()
{
	return this->data;
}

Node * Node::getNext()
{
	return this->nextPtr;
}

void Node::setData(Shape *set)
{
	this->data = set;
}

void Node::setNext(Node *set)
{
	this->nextPtr = set;
}