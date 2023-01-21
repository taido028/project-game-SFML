#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
using namespace sf;
class Enemy
{
private:
	Sprite shape;
	int type;
	float speed;
	int hp;
	int hpmax;
	int damage;
	int point;

	void initVariables();
public:
	Enemy(Texture* texture,float pos_X, float pos_Y);
	virtual ~Enemy();
	// accessor
	const FloatRect getBounds() const;
	const int& getPoints() const; 
	const int& getDamage() const;
	void update(float level);
	void render(RenderTarget* target);
};

