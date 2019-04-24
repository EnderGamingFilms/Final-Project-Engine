#ifndef NODE_H
#define NODE_H
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

#endif