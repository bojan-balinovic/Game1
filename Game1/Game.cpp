#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	// game logic
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;

}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Not Tetris");
	this->window->setFramerateLimit(30);
}


void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimer) {
			this->enemySpawnTimer = 0.f;
			this->spawnEnemy();
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}
	for (int i = 0;i < this->enemies.size();i++) {
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);
		// Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
				deleted = true;
			}
		}
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			deleted = true;
		}
		if (deleted) {
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
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
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(sf::Color::Green);

	//spawn enemy
	this->enemies.push_back(this->enemy);
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

void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePositions();
	this->updateEnemies();
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	// draw game objects

	this->renderEnemies();

	this->window->display();
}
