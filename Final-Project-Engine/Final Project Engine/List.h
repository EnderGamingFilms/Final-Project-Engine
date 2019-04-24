#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Node.h"

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

// List.h:13:2: error: ‘Node’ does not name a type; did you mean ‘modf’?
//   Node * getStart();
//   ^~~~
//   modf
// List.h:21:2: error: ‘Node’ does not name a type; did you mean ‘modf’?
//   Node * start;
//   ^~~~
//   modf
// List.h:22:2: error: ‘Node’ does not name a type; did you mean ‘modf’?
//   Node * end;
//   ^~~~

#endif