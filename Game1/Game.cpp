#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	// GAME LOGIC
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawmTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawmTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	//this->videoMode.getDesktopMode;
	this->window = new sf::RenderWindow(this->videoMode, "FIRST Game done by KOBIELAP", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Green);
	//this->enemy.setOutlineColor(sf::Color::Red);
	//this->enemy.setOutlineThickness(2.f);

}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("No Description Yet");
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
	
		Spawns enemies and sets their color and positions.
		- Sets a random position.
		- Sets a random color.
		- Adds enemy to the vector.

		Tworzenie przeciwników ustawianie koloru oraz pozycji.
		- Ustawienie pozycji jako random
		- Ustawienie koloru jako random
		- Dodanie przeciwnika do vector'a

	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	
	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";
	
	this->uiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::updateMousePositions()
{
	/*
	@return void

	update the mouse postions:
		- Mouse position relative to window(vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
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

	//Moving and updateing enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		// if enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}
//=========================================================
	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView));
				{
					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					//Gain points
					this->points += 1;
					std::cout << "Points: " << this->points << "\n";
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->poolEvents();

	// Update mouse possition
	//std::cout << "Mouse position: " << sf::Mouse::getPosition().x << " <----> " << sf::Mouse::getPosition().y << "\n";

	if (!this->endGame)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	// warunek koncz¹cy grê/End Game Condition
	if (this->health <= 0)
		this->endGame = true;

	// Relative to the window
	/*
	std::cout << "Mouse position to window: " 
		<< sf::Mouse::getPosition(*this->window).x << " <----> " 
		<< sf::Mouse::getPosition(*this->window).y << "\n";
		*/
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
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
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->draw(this->enemy);

	this->window->display();
}



const bool Game::windowIsRunning() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
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
