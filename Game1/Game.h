#pragma once

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <ctime>

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

	// Logika gry/ GAME LOGIC
	unsigned points;
	float enemySpawnTimer;
	float enemySpawmTimerMax;
	int maxEnemies;
	bool mouseHeld;	// sprawdzenie czy klawisz myszki jest held down/przytrzymany 
	

	// Obiekty Gry/Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::Sprite* sprite;
	sf::RectangleShape enemy;

	//Prywatne Funkcje
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	//Konstruktor /Destruktor
	Game();
	virtual ~Game();

	//Akcesoria
	const bool windowIsRunning() const;

	//Funkcje
	void poolEvents();
	void updateMousePositions();
	void update();
	void updateEnemies();
	void render();
	void renderEnemies();
	void spawnEnemy();
};

#endif // !GAME_H




