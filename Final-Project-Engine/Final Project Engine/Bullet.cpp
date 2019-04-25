#include "Init.h"

Bullet::Bullet(float xSpawn, float ySpawn, float size, float speed, float fireAngle)
{
	Hitbox::Init(size / 2);
	Circle::Init(size);

	this->speed = speed;
	this->size = size;
	this->firedAngle = fireAngle;

	this->isInitialized = true;

	Hitbox::Translate(xSpawn, ySpawn);
	Circle::Translate(xSpawn, ySpawn);

}

void Bullet::Init(float xSpawn, float ySpawn, float size, float speed, float fireAngle)
{
	Hitbox::Init(size / 2);
	Circle::Init(size);

	this->speed = speed;
	this->size = size;
	this->firedAngle = fireAngle;

	this->isInitialized = true;

	Hitbox::Translate(xSpawn, ySpawn);
	Circle::Translate(xSpawn, ySpawn);
}

void Bullet::Draw()
{
	Circle::Draw();
}

void Bullet::Fly()
{
	Hitbox::Translate(cos(firedAngle) * speed * SQ_ASPECT_RATIO, sin(firedAngle) * speed);
	Circle::Translate(cos(firedAngle) * speed * SQ_ASPECT_RATIO, sin(firedAngle) * speed);
}