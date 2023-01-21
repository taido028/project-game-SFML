#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<time.h>
using namespace sf;
class Prize
{
private:
	CircleShape shape;
	int hpPlus;
	int damage;
	int point;
	float speed;

	void initVariables();
	void initShape();
public:
	Prize(float pos_X, float pos_Y);
	virtual ~Prize();

	const FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	void update();
	void render(RenderTarget* target);
};

