#include "Init.h"

Enemy::Enemy(float xSpeed, float ySpeed, float rotateSpeed, float size)
{
	this->moveX = xSpeed;
	this->moveY = ySpeed;
	this->moveRotate = rotateSpeed;

	Triangle::Init(size, size, size);
}

void Enemy::Init(float xSpeed, float ySpeed, float rotateSpeed, float size)
{
	this->moveX = xSpeed;
	this->moveY = ySpeed;
	this->moveRotate = rotateSpeed;

	Triangle::Init(size, size, size);
}


Swarm::Swarm(float xSpeed, float ySpeed, float rotateSpeed, float size, unsigned int colorID)
{
	this->numAlive = 0;
	this->color = colorID;
	this->size = size;

	for (int i = 0; i < 16; i++)
	{
		swarm[i].Init(xSpeed, ySpeed, rotateSpeed, size);
		sbox[i].Init(size * 1.6);
		alive[i] = false;
		
		swarm[i].TranslateToOrigin();
		sbox[i].TranslateToOrigin();

		swarm[i].Translate(0, -1 + (size * 2));
		sbox[i].Translate(0, -1 + (size * 2));
	}

	gameBounds.Init(1, true, ((xSpeed + ySpeed) / 2) * 2);

}

void Swarm::Spawn(float x, float y)
{
	if (numAlive < 16)
	{

		for (int i = 0; i < 16; i++)
		{

			if (alive[i] == false)
			{
				alive[i] = true;
				numAlive += 1;

				swarm[i].TranslateToOrigin();
				sbox[i].TranslateToOrigin();

				swarm[i].Translate(x, y);
				sbox[i].Translate(x, y);

				return;
			}
		}
	}
}

void Swarm::Spawn(float x, float y, int seconds, long int vsynccounter)
{
	int target = seconds * 60;

	if (vsynccounter % target == 0)
	{
		Spawn(x, y);
	}

}

int Swarm::checkForDamage(Hitbox &h)
{
	for (int i = 0; i < 16; i++)
	{
		if (alive[i])
		{
			if (sbox[i].isOverlap(h))
			{
				return i;
			}
		}
	}

	return -1;

}


bool Swarm::Kill(int index)
{
	if (index != -1)
	{

		if (alive[index])
		{
			alive[index] = false;
			numAlive -= 1;

			swarm[index].TranslateToOrigin();
			sbox[index].TranslateToOrigin();

			swarm[index].Translate(0, -1 + (size * 2));
			sbox[index].Translate(0, -1 + (size * 2));

			return true;
		}

	}

	return false;
}


void Swarm::Ping()
{

	Boundlimit temp = Unbound;

	for (int i = 0; i < 16; i++)
	{
		if (alive[i])
		{
			if (gameBounds.isInBounds(sbox[i]) != Unbound)
			{
				temp = gameBounds.isInBounds(sbox[i]);

				switch (temp)
				{
				case Lower:
					swarm[i].swapMY();
					break;
				case Left:
					swarm[i].swapMX();
					break;
				case Upper:
					swarm[i].swapMY();
					break;
				case Right:
					swarm[i].swapMX();
					break;
				}


			}

			swarm[i].Translate(swarm[i].getMoveX(), swarm[i].getMoveY());
			sbox[i].Translate(swarm[i].getMoveX(), swarm[i].getMoveY());
			swarm[i].Rotate(swarm[i].getMoveRotate());
			sbox[i].Rotate(swarm[i].getMoveRotate());


			glUseProgram(color);

			swarm[i].Bind();
			swarm[i].BufferVertex();
			swarm[i].Draw();
			swarm[i].Unbind();

			glUseProgram(0);

		}
	}
}

Hitbox * Swarm::getHitBox(int index)
{
	if (alive[index])
	{
		return &sbox[index];
	}

	return nullptr;
}

void Swarm::getMids(int index, float m[2])
{
	if (alive[index])
	{
		swarm[index].CalcMidPoint(m);
	}
	return;
}