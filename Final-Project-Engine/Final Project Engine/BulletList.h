#ifndef BULLETLIST_H
#define BULLETLIST_H
#include "Init.h"

class BulletList : public List 
{
public:
	void iterate(EnemyList &enemies, DestructorList &destructors) { return; }
	bool deleteEnemy(EnemyList &enemies, float *xMid, float *yMid) { return false; }
	bool pushDestructor(DestructorList &destructors, float xMid, float yMid) { return false; }
};

#endif