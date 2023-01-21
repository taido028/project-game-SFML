#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>

using namespace sf;
class Aircraft
{
private:
	Sprite sprite;
	Texture texture;

	float movementspeed;
	float cooldown;
	float cooldownMax;

	int hp;
	int hpMax;
	

	void initVariables();
	void initTexture();
	void initSprite();
	
public:
	Aircraft();
	virtual ~Aircraft();
	//Accessor
	const Vector2f& getPos() const;
	const FloatRect getBounds()const;

	const int& getHp() const;
	const int& getHpMax() const;


	//Modifier
	void setPosition(float const x, float const y);
	void setHp(const int hp);
	void loseHp(const int value);
	void plusHp(const int value);
	

	void move(const float directionX, const float directionY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(RenderTarget& target);
};

