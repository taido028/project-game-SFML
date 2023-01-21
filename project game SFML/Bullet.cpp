#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::Bullet(Texture* texture, float pos_X, float pos_Y, float direction_X, float direction_Y, float movement_speed)
{
	// create the texture of the bullet
	this->shape.setTexture(*texture);
	this->shape.scale(0.33f, 0.33f);
	this->shape.setPosition(pos_X, pos_Y);
	this->direction.x = direction_X;
	this->direction.y = direction_Y;
	this->movementspeed = movement_speed;
}

Bullet::~Bullet()
{

}

const FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//Movement  moves the bullet from its coordinates with 1 velocity
	this->shape.move(this->movementspeed * this->direction);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}
