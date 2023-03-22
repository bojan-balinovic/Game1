#pragma once
#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse position
	sf::Vector2i mousePosWindow;

	// Game objects
	sf::RectangleShape enemy;


	// private functions
	void initVariables();
	void initWindow();
	
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	void initEnemies();

	//accessors
	const bool running() const;

	//functions
	void pollEvents();
	void updateMousePositions();
	void update();
	void render();

};

