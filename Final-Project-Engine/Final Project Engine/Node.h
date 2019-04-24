#pragma once

#include <iostream>

class Node
{
public:
	Node(Shape *set);

	Shape * getData();
	Node * getNext();

	void setData(Shape *set);
	void setNext(Node *next);
private:
	Shape *data;
	Node *nextPtr;
};