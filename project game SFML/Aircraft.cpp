#include "Aircraft.h"
#include<iostream>
using namespace sf;
using namespace std;

void Aircraft::initVariables()
{
	this->movementspeed = 5.f;
	this->cooldownMax = 10.f;
	this->cooldown = this->cooldownMax;

	this->hpMax = 10;
	this->hp = this->hpMax;
}

void Aircraft::initTexture()
{
	if(!this->texture.loadFromFile("texture/jet1.png"))
	{
		cout << "ERROR! Can not open texture file" << "\n";
	}
	this->texture.setSmooth(true);
}

void Aircraft::initSprite()
{
	this->sprite.setTexture(this->texture);
	
	// resize the object
	this->sprite.scale(0.15f, 0.15f);
	
}

Aircraft::Aircraft()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Aircraft::~Aircraft()
{
}

const Vector2f& Aircraft::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Aircraft::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Aircraft::getHp() const
{
	return this->hp;
}

const int& Aircraft::getHpMax() const
{
	return this->hpMax;
}


void Aircraft::setPosition(float const x, float const y)
{
	this->sprite.setPosition(x, y);
}

void Aircraft::setHp(const int hp)
{
	this->hp = hp;
}

void Aircraft::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Aircraft::plusHp(const int value)
{
	this->hp += value;
	if (this->hp > 10)
	{
		this->hp = 10;
	}
}

void Aircraft::move(const float directionX, const float directionY)
{
	this->sprite.move(this->movementspeed * directionX, this->movementspeed * directionY);
}

 // if we attack it will reset theforce
const bool Aircraft::canAttack()
{
	if (this->cooldown >= this->cooldownMax)
	{
		this->cooldown = 0.f;
		return true;
	}
	return false;
}

void Aircraft::updateAttack()
{
	if (this->cooldown < this->cooldownMax)
	{
		this->cooldown += 0.5f;
	}
}


void Aircraft::update()
{
	this->updateAttack();
}

void Aircraft::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
