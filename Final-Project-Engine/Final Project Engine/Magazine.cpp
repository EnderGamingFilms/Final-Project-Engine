#include "Init.h"

Mag::Mag(float speed, float size, unsigned int colorID)
{
	this->size = size;
	this->color = colorID;
	this->speed = speed;

	for (int i = 0; i < MAGAZINE_SIZE; i++)
	{
		InPlay[i] = false;
		buls[i].Init(0, -1 + (size * 2), size, speed, 0);
	}

	gameBounds.Init(1, true, 0);

}

void Mag::Shoot(float spawnX, float spawnY, float theta)
{
	if (numInPlay < MAGAZINE_SIZE)
	{
		for (int i = 0; i < MAGAZINE_SIZE; i++)
		{
			if (InPlay[i] == false)
			{
				InPlay[i] = true;
				buls[i].Init(spawnX, spawnY, this->size, this->speed, theta);
				return;
			}
		}
	}
}

void Mag::Ping()
{
	Boundlimit temp = Unbound;

	glUseProgram(color);

	for (int i = 0; i < MAGAZINE_SIZE; i++)
	{
		if (InPlay[i] == true)
		{
			if (gameBounds.isInBounds(buls[i]) != Unbound)
			{
				//if its out send it back

				DestoryBullet(i);
				//sets inplay index to false
			}
			else
			{
				buls[i].Fly();

				buls[i].Draw();

			}

		}
	}

	glUseProgram(0);
}

void Mag::DestoryBullet(int index)
{
	if (InPlay[index] == true)
	{
		InPlay[index] = false;
		buls[index].Init(0, -1 + (size * 2), size, speed, 0);
	}
}

bool Mag::isContact(Hitbox &h)
{
	for (int i = 0; i < MAGAZINE_SIZE; i++)
	{
		if (InPlay[i])
		{
			if (buls[i].isOverlap(h))
			{
				DestoryBullet(i);
				return true;
			}
		}
	}

	return false;
}