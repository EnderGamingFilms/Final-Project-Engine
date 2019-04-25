#include "Init.h"

List::List()
{
	this->start = nullptr;
	this->end = nullptr;
}

bool List::isEmpty()
{
	if (this->start == nullptr)
		return true;
	else
		return false;
}

Node * List::getStart()
{
	return this->start;
}

void List::insertAtFront(Shape *insert)
{
	if (this->isEmpty())
	{
		this->start = new Node(insert);
		this->end = this->start;
	}
	else
	{
		Node *next = this->start;
		this->start = new Node(insert);
		this->start->setNext(next);
	}
}

void List::insertAtBack(Shape *insert)
{
	if (this->isEmpty())
	{
		this->start = new Node(insert);
		this->end = this->start;
	}
	else
	{
		this->end->setNext(new Node(insert));
		this->end = this->end->getNext();
	}
}

Shape * List::deleteAtFront()
{
	if (this->isEmpty())
		return nullptr;
	else
	{
		Shape *ret = this->start->getData();
		this->start = (this->start->getNext());
		if (this->start = nullptr) //Empty List
			this->end = nullptr;
		return ret;
	}
}

bool List::deleteAtIndex(int index)
{
	Node * current = this->start;
	for (int i = 0; current != nullptr; i++, current = current->getNext())
	{
		if (i == index - 1) //Next node is indexed
		{
			Node * del = current->getNext();
			if (del == nullptr) //At end of list, index does not exist
				return false;
			else //Link current to node 2 ahead
			{
				Node * next = del->getNext();
				current->setNext(next);
				delete del;
				return true;
			}

		}
	}
}

int List::maxIndex()
{
	int index = -1;
	if (this->isEmpty())
		return index;
	for (Node * current = this->start; current != nullptr; current = current->getNext())
		index++;
	return index;
}