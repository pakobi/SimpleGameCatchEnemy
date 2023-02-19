#include <iostream>
#include "Game.h"

/*
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
*/
const int lnktest1 = 0;

using namespace sf;


int main()
{
	
	// Init srand
	srand(static_cast<unsigned>(time(NULL)));
	
	// Init Game Window
	Game game;
	
	//Game loop
	while (game.windowIsRunning() && !game.getEndGame())
	{

		// Update
		game.update();
				
		// Render
		game.render();

		//window.clear(sf::Color::Yellow); //Clear old frame

		// Draw your game
		//window.display(); // Tell app that window is done drawing

	}

	return 0;
}