#include "Prize.h"

void Prize::initVariables()
{
	this->hpPlus = 1;
	this->damage = 1;
	this->point = 1;
	this->speed = 0.5;//rand() % 3;
}

void Prize::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(4);
	this->shape.setFillColor(Color::White);
}

Prize::Prize(float pos_X, float pos_Y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_X, pos_Y);
}

Prize::~Prize()
{
}

const FloatRect Prize::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Prize::getPoints() const
{
	return point;
}

const int& Prize::getDamage() const
{
	return this->damage;
}

void Prize::update()
{
	this->shape.move(0.f, this->speed);
}

void Prize::render(RenderTarget* target)
{
	target->draw(this->shape);
}
