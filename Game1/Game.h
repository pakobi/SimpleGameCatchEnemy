#pragma once

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
	Klasa pe³ni¹ca rolê silnika Gry/ GAME ENGINE CLASS.
	Wrapper class.

*/

class Game
{
private:

	// Zmienne/Variables


	// Okna/Window
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Mouse postions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;
	sf::Text uiText;

	// Logika gry/ GAME LOGIC
	unsigned points;
	float enemySpawnTimer;
	float enemySpawmTimerMax;
	int maxEnemies;
	bool mouseHeld;	// sprawdzenie czy klawisz myszki jest held down/przytrzymany 
	int health; // liczba ¿yæ
	bool endGame; // znacznik koñca gry
	

	// Obiekty Gry/Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::Sprite* sprite;
	sf::RectangleShape enemy;

	//Prywatne Funkcje
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();


public:
	//Konstruktor /Destruktor
	Game();
	virtual ~Game();

	//Akcesoria
	const bool windowIsRunning() const;
	const bool getEndGame() const;

	//Funkcje
	void poolEvents();
	void updateMousePositions();
	void update();
	void updateText();
	void updateEnemies();

	void render();
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void spawnEnemy();
};

#endif // !GAME_H




