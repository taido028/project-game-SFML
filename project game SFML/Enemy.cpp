#include "Enemy.h"
#include<time.h>

void Enemy::initVariables()
{
	this-> type = 0;
	this-> speed = 3.f;
	this-> hpmax = static_cast<int>(10);
    this-> hp = this->hpmax;
	this-> damage = 1;
	this-> point = rand()%20+5;
}

Enemy::Enemy(Texture* texture,float pos_X,float pos_Y)
{
	//create the texture of the enemy
	this->shape.setTexture(*texture);
	this->shape.scale(((double)rand()) / ((double)RAND_MAX) / 3.0 + 0.05, ((double)rand()) / ((double)RAND_MAX) / 3.0 + 0.05);
	this->shape.setPosition(pos_X, pos_Y);
	this->initVariables();
}

Enemy::~Enemy()
{

}

const FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->point;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}



void Enemy::update(float level)
{
	
	this->shape.move(0.f, this->speed + level);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->shape);
}
