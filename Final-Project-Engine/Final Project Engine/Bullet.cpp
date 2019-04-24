#include "Init.h"

Bullet::Bullet(float xSpawn, float ySpawn, float size, float speed, float fireAngle)
{
	Shader *localColor = this->getShader();
	localColor->Create("u_Color");
	localColor->setRgb(0, 0, 1);
	localColor->Use();
	localColor->UpdateUniform();
	localColor->unBind();
	
	Hitbox::Init(size / 2);
	//Circle::Init(size);
	circleShape.Init(size);

	this->speed = speed;
	this->size = size;
	this->firedAngle = fireAngle;

	this->isInitialized = true;

	Hitbox::Translate(xSpawn, ySpawn);
	//Circle::Translate(xSpawn, ySpawn);
	circleShape.Translate(xSpawn, ySpawn);

}

void Bullet::Init(float xSpawn, float ySpawn, float size, float speed, float fireAngle)
{
	Hitbox::Init(size / 2);
	//Circle::Init(size);
	circleShape.Init(size);

	this->speed = speed;
	this->size = size;
	this->firedAngle = fireAngle;

	this->isInitialized = true;

	Hitbox::Translate(xSpawn, ySpawn);
	//Circle::Translate(xSpawn, ySpawn);
	circleShape.Translate(xSpawn, ySpawn);
}

void Bullet::Draw()
{
	this->getShader()->Use();
	
	//Circle::Draw();
	circleShape.Draw();
	
	this->getShader()->unBind();
}

void Bullet::Fly()
{
	Hitbox::Translate(cos(firedAngle) * speed * SQ_ASPECT_RATIO, sin(firedAngle) * speed);
	//Circle::Translate(cos(firedAngle) * speed * SQ_ASPECT_RATIO, sin(firedAngle) * speed);
	circleShape.Translate(cos(firedAngle) * speed * SQ_ASPECT_RATIO, sin(firedAngle) * speed);
}

int Bullet::iterate()
{
	this->Fly();
	this->Draw();
	return FALSE_ITERATE;
}