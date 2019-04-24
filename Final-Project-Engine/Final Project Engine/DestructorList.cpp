#include "Init.h"

void DestructorList::iterate()
{
	Node *current = this->getStart(), *prev = nullptr;
	int iterateStatus = 0;
	for (int i = 0; current != nullptr; i++)
	{
		EnemyExplode * data = dynamic_cast<EnemyExplode *>(current->getData());
		iterateStatus = data->iterate();
		if (iterateStatus == FALSE_ITERATE)
		{
			current = current->getNext(); //Prev stays the same b/c current node will be deleted
			this->deleteAtIndex(i);
		}
		else
		{
			prev = current;
			current = current->getNext();
		}
	}

}