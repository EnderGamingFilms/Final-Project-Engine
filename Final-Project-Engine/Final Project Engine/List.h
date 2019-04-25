#pragma once

#include <iostream>

#define FALSE_ITERATE -1 //No iteration action needed

class List
{
public:
	List();

	bool isEmpty();
	Node * getStart();
	void insertAtFront(Shape *insert);
	void insertAtBack(Shape *insert);
	Shape * deleteAtFront();
	bool deleteAtIndex(int index);
	int maxIndex();

private:
	Node * start;
	Node * end;
};