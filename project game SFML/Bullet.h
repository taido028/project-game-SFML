#ifndef BULLET_H
#define BULLET_H
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace sf;
class Bullet
{
private:
	Sprite shape;
	Vector2f direction;
	float movementspeed;

public:
	Bullet();
	Bullet(Texture* texture,float pos_X, float pos_Y, float direction_X, float direction_Y, float movement_speed);
	virtual ~Bullet();

	// Accessor
	const FloatRect getBounds() const;

	void update();
	void render(RenderTarget* target);
};

#endif // !BULLET_H