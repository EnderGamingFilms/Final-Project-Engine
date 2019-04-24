#include "Init.h"

Enemy::Enemy()
{
	Shader *localColor = this->getShader();
	localColor->Create("u_Color");
	localColor->setRgb(1, 0, 0);
	localColor->Use();
	localColor->UpdateUniform();
	localColor->unBind();
	
	Rectangle::Init(ENEMY_SIZE, ENEMY_SIZE);


	this->xSpeed = rand() % 10 / (float)1000;
	this->ySpeed = rand() % 10 / (float)1000;

	this->spawn[0] = rand() % 100 / (float)100;
	this->spawn[1] = rand() % 100 / (float)100;

	box.Init(ENEMY_SIZE);
	border.Init(1, true, 0.005);

	box.Translate(spawn[0], spawn[1]);
	Rectangle::Translate(spawn[0], spawn[1]);
}

Enemy::~Enemy(){}

Enemy::Enemy(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY)
{
	Shader *localColor = this->getShader();
	localColor->Create("u_Color");
	localColor->setRgb(1, 0, 0);
	localColor->Use();
	localColor->UpdateUniform();
	localColor->unBind();
	
	Rectangle::Init(ENEMY_SIZE, ENEMY_SIZE);


	this->xSpeed = xNewSpeed;
	this->ySpeed = yNewSpeed;

	this->spawn[0] = spawnX;
	this->spawn[1] = spawnY;

	box.Init(ENEMY_SIZE);
	border.Init(1, true, 0.005);

	box.Translate(spawn[0], spawn[1]);
	Rectangle::Translate(spawn[0], spawn[1]);
}



void Enemy::init(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY)
{
	Rectangle::Init(ENEMY_SIZE, ENEMY_SIZE);


	this->xSpeed = xNewSpeed;
	this->ySpeed = yNewSpeed;

	this->spawn[0] = spawnX;
	this->spawn[1] = spawnY;

	box.Init(ENEMY_SIZE);
	border.Init(1, true, 0.005);

	box.Translate(spawn[0], spawn[1]);
	Rectangle::Translate(spawn[0], spawn[1]);
}

int Enemy::iterate()
{
	this->draw();
	
	Boundlimit lim = Unbound;
	if (border.isInBounds(box) == Upper)
	{
		this->setMoveY((-1 * ySpeed));
		cout << "hit upper";
	}
	else if (border.isInBounds(box) == Lower)
	{
		this->setMoveY((-1 * ySpeed));
	}
	else if (border.isInBounds(box) == Left)
	{
		this->setMoveX((-1 * xSpeed));
	}
	else if (border.isInBounds(box) == Right)
	{
		this->setMoveX((-1 * xSpeed));
	}

	Rectangle::Translate(this->xSpeed, this->ySpeed);
	box.Translate(this->xSpeed, this->ySpeed);

	return 1;
}

void Enemy::setMoveX(const float &moveX)
{
	this->xSpeed = moveX;
}


void Enemy::setMoveY(const float &moveY)
{
	this->ySpeed = moveY;
}

void Enemy::draw()
{
	this->getShader()->Use();
	
	this->Rectangle::Bind();
	this->Rectangle::BufferVertex();
	this->Rectangle::Draw();
	this->Rectangle::Unbind();

	this->box.Bind();
	this->box.BufferVertex();
	this->box.Draw();
	this->box.Unbind();

	this->getShader()->unBind();
}

Hitbox * Enemy::getHitBox()
{
	return &this->box;
}