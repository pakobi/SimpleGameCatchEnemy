#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	// GAME LOGIC
	this->points = 0;
	this->enemySpawmTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawmTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode;
	this->window = new sf::RenderWindow(this->videoMode, "FIRST Game done by KOBIELAP", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Funkcje
void Game::spawnEnemy()
{
	/*
		@return void
	
		Spawns enemies and setrs their color and positions.
		- Sets a random position.
		- Sets a random color.
		- Adds enemy to the vector.

		Tworzenie przeciwników ustawianie koloru oraz pozycji.
		- Ustawienie pozycji jako random
		- Ustawienie koloru
		- Dodanie przeciwnika do vector'a

	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	
	this->enemy.setFillColor(sf::Color::Red);

	this->enemies.push_back(this->enemy);
}

void Game::updateMousePositions()
{
	/*
	@return void

	update the mouse postions:
		- Mouse position relative to window(vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
	/**
	@return void

		Updates the enemy spawn timer and spawns enemies.
		When the total amount of enemies is smaller than the max.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen.

		Aktualizacja czasu tworzenia przeciwnika oraz liczby przeciwników
		Je¿eli liczba przeciwników jest mniejsza ni¿ maksymalna
		to przesuñ przeciwka w kierunku dolnym
		Usuwanie przeciwników na koñcu ekranu
	*/
	
	
	// Updating Timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawmTimerMax)
		{
		//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (auto& e : this->enemies)
	{
		e.move(0.f, 1.f);
	}

}

void Game::update()
{
	this->poolEvents();

	// Update mouse possition
	//std::cout << "Mouse position: " << sf::Mouse::getPosition().x << " <----> " << sf::Mouse::getPosition().y << "\n";


	this->updateMousePositions();

	this->updateEnemies();

	// Relative to the window
	/*
	std::cout << "Mouse position to window: " 
		<< sf::Mouse::getPosition(*this->window).x << " <----> " 
		<< sf::Mouse::getPosition(*this->window).y << "\n";
		*/
}

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}


void Game::render()
{
	/*
	@return void

	Always clear window first
	- clear old frame
	- render objects
	- display frame in window
	
	Render the game objects
	*/
	
	
	this->window->clear(sf::Color(0, 0, 0, 0));

	//Draw game objects
	this->renderEnemies();

	this->window->draw(this->enemy);

	this->window->display();
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Green);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(2.f);

}

const bool Game::windowIsRunning() const
{
	return this->window->isOpen();
}

void Game::poolEvents()
{
	// Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}

}
