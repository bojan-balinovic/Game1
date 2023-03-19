#pragma once
#include  "SFML/Graphics.hpp" // replace quotes with less than and greater than symbols

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	
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
	void update();
	void render();

};

