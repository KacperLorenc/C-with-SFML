#include "Game.h"


//Functions

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "ERROR::GAME::INITFONTS::COULD NOT LOAD FONT \n";
	}
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setCharacterSize(32);

	this->endGameText.setFont(this->font);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(280.f, 225.f));
	this->endGameText.setString("Game Over!");
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else {
		if (this->Balls.size() < this->maxBalls) {
			
			this->Balls.push_back(Ball(*this->window, this->randomizeType()));
			this->spawnTimer = 0.f;
		}
	}
}

void Game::updateCollision()
{
	//Check the collision 
	for ( size_t i = 0; i <this->Balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->Balls[i].getShape().getGlobalBounds())) {

			switch (this->Balls[i].getType()) {

			case ballTypes::DEFAULT:
				//Add points
				this->points += 5;
				break;
			case ballTypes::DAMAGING:
				//Take damage
				this->player.takeDamage(3);
				break;
			case ballTypes::HEALING:
				//Heal
				this->player.gainHealth(1);
				break;

			}

			//Remove balls
			this->Balls.erase(this->Balls.begin() + i);
		}
	}
	
}

const int Game::randomizeType() const
{
	int type = ballTypes::DEFAULT;
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 90) {
		type = ballTypes::DAMAGING;
	}
	else if (randValue > 90) {
		type = ballTypes::HEALING;
	}
	

	return type;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) {

		switch (this->sfmlEvent.type) {

			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Points:  ";
	ss << this->points<<"\n";
	ss << "Health: ";
	ss << this->player.getHp()<< " / " << this->player.getHpMax();

	this->guiText.setString(ss.str());
}

void Game::updatePlayer()
{
	this->player.update(this->window);
	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::update()
{
	this->pollEvents();
	if (this->endGame == false) {
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

void Game::render()
{
	this->window->clear();

	this->player.render(this->window);

	for (auto i : this->Balls) {
		i.render(*this->window);
	}
	this->renderGui(this->window);

	if (this->endGame == true) {
		this->window->draw(this->endGameText);
	}

	this->window->display();

}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

//Constructors and destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();	
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}
