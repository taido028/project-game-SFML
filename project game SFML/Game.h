#pragma once
#include "Aircraft.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Prize.h"
#include<iostream>
#include<sstream>
#include<map>
#include<string>
#include<numeric>
using namespace sf;
using namespace std;
class Game
{
private:
	//Window
	RenderWindow* window;

	//Resources
	map<string, Texture*> textures;
	vector <Bullet*> bullets;

	//GUI
	Font font;
	Text pointText;
	Text GameOverText;

	//Background
	Sprite background;
	Texture backgroundText;

	//System
	unsigned points;
	vector<float> totalpoints;
	

	//Player
	Aircraft* player;

	//PlayerGUI
	RectangleShape HpBar;
	RectangleShape HpBarBack;

	// Enemy
	float spawnTimer;
	float spawnTimerMax;
	vector<Enemy*> enemies;

	//Prizes
	float spawnPrizeTimer;
	float spawnPrizeTimerMax;
	vector<Prize*> prizes;

	void initWindow();
	void initTextures();
	void initTexturesEnemies();
	void initGUI();
	void initBackground();
	void initSystems();
	void initPlayer();
	void initEnemies();
	void initPrizes();
	
public:
	Game();
	virtual ~Game();

	void run();

	void UpdatePollEvent();
	void UpdateInput();
	void UpadteGUI();
	void UpdateCollision();
	void UpdateBullets();
	void UpdateEnemies(float level);
	void UpdatePrizes();
	void UpdateShooting();
	void UpdateLevel();
	void update();
	void renderGUI();
	void renderBackground();
	void render();
};
