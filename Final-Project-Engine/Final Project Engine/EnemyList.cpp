#include "Init.h"

void EnemyList::iterate()
{
	for (Node *current = this->getStart(); current != nullptr; current = current->getNext())
	{
		Enemy *enemyUnit = dynamic_cast<Enemy *>(current->getData());
		enemyUnit->iterate();
	}
}