#include "Init.h"

void BulletList::iterate(EnemyList &enemies, DestructorList &destructors)
{
	float enemyX = 0, enemyY = 0;
	int bulletIndex = 0;
	for (Node * current = this->getStart(), * prev = nullptr; current != nullptr; bulletIndex++)
	{
		Bullet *currentBullet = dynamic_cast<Bullet *>(current->getData());
		if (gameBound.isInBounds(*currentBullet))
		{
			current = prev;
			this->deleteAtIndex(bulletIndex);
		}
		currentBullet->iterate();
		Node * currentEnemyNode = enemies.getStart();
		for (int enemyIndex = 0; currentEnemyNode != nullptr; enemyIndex++) //Check current bullet against all enemies in list
		{
			Enemy * currentEnemy = dynamic_cast<Enemy *>(currentEnemyNode->getData());
			if (currentBullet->isOverlap(*(currentEnemy->getHitBox()))) //Hit with enemy
			{
				float curX = 0, curY = 0;
				currentEnemyNode = currentEnemyNode->getNext();
				if (deleteEnemy(enemies, enemyIndex, &curX, &curY))
					pushDestructor(destructors, curX, curY);
			}
			else
				currentEnemyNode = currentEnemyNode->getNext();
		}
		prev = current;
		if (current != nullptr)
			current = current->getNext();
	}
}

bool BulletList::deleteEnemy(EnemyList &enemies, int index, float *xMid, float *yMid)
{
	Enemy *del = dynamic_cast<Enemy *> (enemies.getIndex(index)->getData());
	float locArray[2] = { 0 };
	del->CalcMidPoint(locArray);
	*xMid = locArray[0] / SQ_ASPECT_RATIO;
	*yMid = locArray[1];
	return enemies.deleteAtIndex(index);
}

void BulletList::pushDestructor(DestructorList &destructors, float xMid, float yMid)
{
	destructors.insertAtBack(new EnemyExplode(xMid, yMid, ENEMY_SIZE));
}