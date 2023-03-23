#include "Game.h"

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font" << std::endl;
	}

}

void Game::initVariables()
{
	this->window = nullptr;

	// game logic
	this->endGame = false;
	this->health = 10;
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;

}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Not Tetris");
	this->window->setFramerateLimit(30);
}

void Game::initTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setPosition(50, 50);
	this->uiText.setString("NONE");

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
	bool deleted = false;
	for (int i = 0;i < this->enemies.size();i++) {

		this->enemies[i].move(0.f, 5.f);
		// Check if clicked upon

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			deleted = true;
			this->health -= 1;
			std::cout << "health: "<<this->health << std::endl;

		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			mouseHeld = true;
			for (size_t i = 0;i < this->enemies.size() && deleted == false;i++) {
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 1;
					std::cout << "points: "<<this->points << std::endl;
				}
			}
		}
	}
	else {
		mouseHeld = false;
	}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initFonts();
	this->initTexts();
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

const bool Game::getEndGame() const
{
	return this->endGame;
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
	if (!this->endGame) {
		this->updateMousePositions();
		this->updateEnemies();
	}
	if (this->health <= 0) {
		this->endGame = true;
	}
	this->updateText();
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->uiText.setString(ss.str());
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();

	// draw game objects

	this->renderEnemies();
	this->renderText(*this->window);

	this->window->display();
}
