#pragma once
#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols
#include <vector>
#include <ctime>

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

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float maxEnemies;


	// private functions
	void initVariables();
	void initWindow();
	void updateEnemies();
	
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	void initEnemies();

	//accessors
	const bool running() const;

	//functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void update();

	void renderEnemies();
	void render();

};

