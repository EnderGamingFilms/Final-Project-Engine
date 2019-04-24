#pragma once

#include "List.h"
#include "EnemyList.h"
#include "DestructorList.h"

class BulletList : public List
{
public:
	BulletList() { gameBound.Init(1, true, 0.005); }
	void iterate(EnemyList &enemies, DestructorList &destructors);
	bool deleteEnemy(EnemyList &enemies, int index, float *xMid, float *yMid);
	void pushDestructor(DestructorList &destructors, float xMid, float yMid);
private:
	Bounds gameBound;
};