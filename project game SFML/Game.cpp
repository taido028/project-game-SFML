#include "Game.h"

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(800, 600), "Game", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("texture/bullet.png");
}

void Game::initTexturesEnemies()
{
	this->textures["ENEMIES"] = new Texture();
	this->textures["ENEMIES"]->loadFromFile("texture/tt.png");
}

void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("Font/Arimo-Regular.ttf")) 
	{
		cout << "Failed to load font " << "\n";
	}
	
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("Game");
	
	this->GameOverText.setFont(this->font);
	this->GameOverText.setCharacterSize(50);
	this->GameOverText.setFillColor(Color::Red);
	this->GameOverText.setString("Game Over!");
	this->GameOverText.setPosition(this->window->getSize().x / 2.f - this->GameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->GameOverText.getGlobalBounds().height / 2.f);

	this->Return.setFont(this->font);
	this->Return.setCharacterSize(50);
	this->Return.setFillColor(Color::Red);
	this->Return.setString("Please press ESC to return");
	this->Return.setPosition(this->window->getSize().x / 2.f- this->Return.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - this->Return.getGlobalBounds().height / 3.f );

	this->HighScore.setFont(this->font);
	this->HighScore.setCharacterSize(20);
	this->HighScore.setFillColor(Color::Red);
	this->HighScore.setString("Highest score: ");
	this->HighScore.setPosition(0,35.f);

	// init playerGUI
	this->HpBar.setSize(Vector2f(250.f, 20.f));
	this->HpBar.setFillColor(Color::Red);
	this->HpBar.setPosition(Vector2f(20.f, 20.f));

	this->HpBarBack = this->HpBar;
	this->HpBarBack.setFillColor(Color(25, 25, 25, 200));
}

void Game::initBackground()
{
	if (!this->backgroundText.loadFromFile("texture/background.jpg"))
	{
		cout << " Failed to load background " << "\n";
	}
	this->background.setTexture(this->backgroundText);
	
}


void Game::initSystems()
{
	this->points = 0;
}


void Game::initPlayer()
{
	this->player = new Aircraft();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 75.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initPrizes()
{
	this->spawnPrizeTimerMax = 200.f;
	this->spawnPrizeTimer = this->spawnPrizeTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initTexturesEnemies();
	this->initGUI();
	this->initBackground();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initPrizes();
	
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	// delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	// delete bullet
	for (auto* i : this->bullets)
	{
		delete i;
	}
	// delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	// delete prizes
	for (auto* i : this->prizes)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->UpdatePollEvent();
		if (this->player->getHp() > 0)
		{
			this->update();
		}
		this->render();
	}
}

void Game::UpdatePollEvent()
{
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.Event::type == Event::Closed)
		{
			this->window->close();
		}
		if (event.KeyPressed && event.Event::key.code == Keyboard::Escape)
		{
			this->window->close();
		}
	}
	
}

void Game::UpdateInput()
{
	// Move object along the x, y axes vector with 1 velocity.
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}
	if (Mouse::isButtonPressed(Mouse::Left)&& this->player->canAttack())
	{
		//when clicking the left mouse, the bullet will appear at the 
		//current position of the aircraft and upward with 1 velocity 
	    //and i want to make sure that the bullet comes from the middle of the object

		this->bullets.push_back(new Bullet(this->textures["BULLET"], 
			this->player->getPos().x + this->player->getBounds().width/10.f,    
			this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::UpadteGUI()
{
	stringstream s;
	s << "Points: " << this->points;
	this->pointText.setString(s.str());

	//Update player GUI
	
	float HpPercent=static_cast<float>(this->player->getHp())/this->player->getHpMax();
	this->HpBar.setSize(Vector2f(250.f* HpPercent , this->HpBar.getSize().y));

}

// Function that keeps the object do not reach outside of the screen
void Game::UpdateCollision()
{
	if(this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

}

void Game::UpdateBullets()
{
	unsigned count = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// delete the bullet if out of the screen
			delete this->bullets.at(count);
			this->bullets.erase(this->bullets.begin() + count);
			
		}
		++count;
	}
}

void Game::UpdateEnemies(float level)
{
	//Spawning enemies
	this->spawnTimer += 0.3f + level;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(this->textures["ENEMIES"],rand() % this->window->getSize().x-20.f , -100.f));
		this->spawnTimer = 0.f;
	}
	// Update 
	unsigned count = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update(level);
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			// delete enemies if out of the screen
			this->player->loseHp(this->enemies.at(count)->getDamage());
			delete this->enemies.at(count);
			this->enemies.erase(this->enemies.begin() + count);
		}
			//Enemy and player collision, player will lose hp if collide with enemy
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(count)->getDamage());
			delete this->enemies.at(count);
			this->enemies.erase(this->enemies.begin() + count);
		}
		++count;
		
	}
}

void Game::UpdatePrizes()
{
	//Spawning prizes
	this->spawnPrizeTimer += 0.2f;
	if (this->spawnPrizeTimer >= this->spawnPrizeTimerMax)
	{
		this->prizes.push_back(new Prize(rand() % this->window->getSize().x - 20.f , -100.f));
		this->spawnPrizeTimer = 0.f;
	}
	// Update
	unsigned count = 0;
	for (auto* prize : this->prizes)
	{
		prize->update();
		if (prize->getBounds().top > this->window->getSize().y)
		{
			// delete prizes if out of the screen
			delete this->prizes.at(count);
			this->prizes.erase(this->prizes.begin() + count);
		}
		//Prize and player collision, player will regen HP if collide with prize 
		else if (prize->getBounds().intersects(this->player->getBounds()))
		{
			this->points += this->prizes.at(count)->getPoints();
			this->player->plusHp(this->prizes.at(count)->getDamage());
			delete this->prizes.at(count);
			this->prizes.erase(this->prizes.begin() + count);
			
		}
		++count;
	}

}

void Game::UpdateShooting()
{
	// delete bullets when bullet hit target and get points
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size()&& enemy_deleted==false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				enemy_deleted = true;
			}
		}
	}
	// delete prizes when bullet hit target and get points and regen
	for (int i = 0; i < this->prizes.size(); i++)
	{
		bool prize_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && prize_deleted == false; k++)
		{
			if (this->prizes[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->player->plusHp(1);
				this->points += this->prizes[i]->getPoints();
				delete this->prizes[i];
				this->prizes.erase(this->prizes.begin() + i);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				prize_deleted = true;
			}
		}
	}
}

void Game::UpdateLevel()
{   // level 1
	if (this->points >=0 && this->points<=50)
	{
		UpdateEnemies(0);
	}
	// level 2
	else if(this->points>50 && this->points<=350)
	{
		UpdateEnemies(0.5);
	}
	// level 3
	else if(this->points > 350 && this->points <= 800)
	{
		UpdateEnemies(1);
	}
	// level 4
	else if (this->points > 800 && this->points <= 1500)
	{
		UpdateEnemies(1.5);
	}
	// level 5
	else if (this->points > 1500 && this->points <= 3000)
	{
		UpdateEnemies(2.5);
	}
	// level 6
	else
	{
		UpdateEnemies(4);
	}
}

void Game::update()
{
	this->UpdateInput();
	this->player->update();
	this->UpdateCollision();
	this->UpdateBullets();
	//this->UpdateEnemies();
	this->UpdateLevel();
	this->UpdatePrizes();
	this->UpdateShooting();
	this->UpadteGUI();
	this->UpdateHS();
}
// Update high score 
void Game::UpdateHS()
{
	ifstream readFile;
	string hs;
	readFile.open("Highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highscore;
		}
	}
	readFile.close();

	ofstream writeFile("Highscore.txt");
	if (writeFile.is_open())
	{
		if (this->points > highscore)
		{
			highscore = this->points;
		}
		writeFile << highscore;
	}
	writeFile.close();
	
}


void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->HpBarBack);
	this->window->draw(this->HpBar);
}

void Game::renderBackground()
{
	this->window->draw(this->background);
	
}


void Game::render()
{
	this->window->clear();
	// draw all the stuffs
	this->renderBackground();
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	for (auto* prize : this->prizes)
	{
		prize->render(this->window);
	}
	this->renderGUI();
	// game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->GameOverText);
		this->window->draw(this->Return);
		ifstream file;
		file.open("Highscore.txt");
		string hs;
		while (!file.eof())
		{
			file >> hs;
		}
		stringstream s;
		s << " Highest score: " << hs;
		this->HighScore.setString(s.str());
		this->window->draw(this->HighScore);
	}
	this->window->display();
}
