#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Not Tetris");
	this->window->setFramerateLimit(144);
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

void Game::initEnemies()
{
	//this->enemy.setPosition();
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		if (ev.type == sf::Event::Closed) {

			this->window->close();
		}
		switch (ev.type) {
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{

	this->window->clear(sf::Color(255, 0, 0, 255));

	// draw game objects
	this->window->draw(this->enemy);

	this->window->display();
}
