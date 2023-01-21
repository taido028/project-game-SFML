#include "Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<time.h>
int main()
{
	
	srand(time(0));
	Game game;

	game.run();

	return 0;
}