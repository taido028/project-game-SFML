#include "Game.h"
#include "MainMenu.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<time.h>
#include<fstream>
int main()
{
	RenderWindow MENU(VideoMode(800, 600), "Main Menu", Style::Default);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	// init background for main menu
	RectangleShape MainMenuBackground;
	Texture MainMenuTexture;
	MainMenuBackground.setSize(Vector2f(800, 600));
	MainMenuTexture.loadFromFile("texture/background.jpg");
	MainMenuBackground.setTexture(&MainMenuTexture);

	// init background for high score
	RectangleShape HighScoreBackground;
	Texture HighScoreTexture;
	HighScoreBackground.setSize(Vector2f(800, 600));
	HighScoreTexture.loadFromFile("texture/backgroundHS.jpg");
	HighScoreBackground.setTexture(&HighScoreTexture);

	// init background for instruction
	RectangleShape InsBackground;
	Texture InsTexture;
	InsBackground.setSize(Vector2f(800, 600));
	InsTexture.loadFromFile("texture/backgroundIS.jpg");
	InsBackground.setTexture(&InsTexture);

	Font HighScoreFont;

	Text HighScoreText;
	Text HighestscoreT;
	if (!HighScoreFont.loadFromFile("Font/Arimo-Regular.ttf"))
	{
		cout << "Failed to load font " << "\n";
	}


	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up||event.key.code==Keyboard::W)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return)
				{
					RenderWindow INSTRUCTION(VideoMode(800, 600), "OPTIONS");
					RenderWindow HIGHSCORE(VideoMode(800, 600), "HIGH SCORE");
					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						srand(time(0));
						Game game;
						game.run();
						INSTRUCTION.close();
						HIGHSCORE.close();
					}
					if (x == 1)
					{
						while (HIGHSCORE.isOpen())
						{
							ifstream file;
							file.open("Highscore.txt");
							string hs;
							while (!file.eof())
							{
								file >> hs;
							}
							stringstream s;
							s << hs;

							Event event;
							HighScoreText.setFont(HighScoreFont);
							HighScoreText.setFillColor(Color::White);
							HighScoreText.setString("Your highest score is: ");
							HighScoreText.setCharacterSize(70);
							HighScoreText.setPosition(75, 200);

							HighestscoreT.setFont(HighScoreFont);
							HighestscoreT.setFillColor(Color::White);
							HighestscoreT.setString("Score:");
							HighestscoreT.setCharacterSize(70);
							HighestscoreT.setPosition(75, 300);
							HighestscoreT.setString(s.str());
							
							while (HIGHSCORE.pollEvent(event))
							{
								if (event.type == Event::Closed)
								{
									HIGHSCORE.close();
								}
								if (event.type == Event::KeyPressed)
								{
									if (event.key.code == Keyboard::Escape)
									{
										HIGHSCORE.close();
									}
								}
							}
							INSTRUCTION.close();
							HIGHSCORE.clear();
							HIGHSCORE.draw(HighScoreBackground);
							HIGHSCORE.draw(HighScoreText);
							HIGHSCORE.draw(HighestscoreT);
							HIGHSCORE.display();
						}
					}
					if (x == 2)
					{
						while (INSTRUCTION.isOpen())
						{
							Event event;
							while (INSTRUCTION.pollEvent(event))
							{
								if (event.type == Event::Closed)
								{
									INSTRUCTION.close();
								}
								if (event.type == Event::KeyPressed)
								{
									if (event.key.code == Keyboard::Escape)
									{
										INSTRUCTION.close();
									}
								}
							}
							HIGHSCORE.close();
							INSTRUCTION.clear();
							INSTRUCTION.draw(InsBackground);
							INSTRUCTION.display();
						}
					}
					if (x == 3)
					{
						MENU.close();
					}
					break;
				}
			}
		}
		MENU.clear();
		MENU.draw(MainMenuBackground);
		mainMenu.draw(MENU);
		MENU.display();
	}
	
	return 0;
}