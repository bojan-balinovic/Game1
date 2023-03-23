#pragma once
#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float maxEnemies;
	bool mouseHeld;

	// private functions
	void initFonts();
	void initVariables();
	void initWindow();
	void initTexts();
	void updateEnemies();

public:
	//constructors / destructors
	Game();
	virtual ~Game();

	void initEnemies();

	//accessors
	const bool running() const;
	const bool getEndGame() const;

	//functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void update();
	void updateText();

	void renderEnemies();
	void renderText(sf::RenderTarget& target);
	void render();

};

