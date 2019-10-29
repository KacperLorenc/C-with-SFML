#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
	
	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 6;
	this->isMouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Learn shooting!", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.otf")) {

		std::cout << "ERROR::INITFONTS::Failed to load font"<<"\n";

	}
}
void Game::initText(){

	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}
//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initText();
	this->initFonts();
	
	
}

Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}





//Functions
void Game::spawnEnemies()
{
	/*
	
	Spawns enemies and sets their types, colors and positions randomly
	-Sets a random type
	-Sets a random position
	-Sets a random color
	-Adds enemy to the vector

	*/

this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x -2*( this->enemy.getSize().x))),
		-(this->enemy.getSize().y)
	);
		
	//Randomize enemy type

int type = rand() % 5;

switch (type) {

case 0:
	this->enemy.setSize(sf::Vector2f(15.f, 15.f));
	this->enemy.setFillColor(sf::Color::Red);
	break;
case 1:
	this->enemy.setSize(sf::Vector2f(25.f, 25.f));
	this->enemy.setFillColor(sf::Color::Blue);
	break;
case 2:
	this->enemy.setSize(sf::Vector2f(35.f, 35.f));
	this->enemy.setFillColor(sf::Color::Magenta);
	break;
case 3:
	this->enemy.setSize(sf::Vector2f(45.f, 45.f));
	this->enemy.setFillColor(sf::Color::Yellow);
	break;
default:
	this->enemy.setSize(sf::Vector2f(55.f, 55.f));
	this->enemy.setFillColor(sf::Color::Green);
	break;

}

	

		//Spawns enemy - adds enemy to the vector
		this->enemies.push_back(this->enemy);

}

void Game::pollEvents()
{
	//Event polling

		/*
		
		pollEvent - Pop the event on top of the event queue, if any, and return it.
		This function is not blocking: if there's no pending event then it will return false and leave event unmodified.
		
		*/

	while (this->window->pollEvent(this->event)) {

		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{

	this->mousePosWindow = sf::Mouse::getPosition(*this->window); // dereferencing because window is a pointer and this takes a reference to a window
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateEnemies()
{
	/*
	
	-Updates the enemy spawn timer and spawns enemies
	when total amount of enemies is smaller than the maximum
	-Moves the enemies downwards
	-Removes the enemies athe the edge of the screen
	
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {

		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//Spawn the enemy and reset the timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;

	}

	//Moving and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++) {

		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		//Check if the enemy is at the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			this->health += -1;
			std::cout << "Health: " << this->health << "\n";
		}

	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (this->isMouseHeld == false) {

			this->isMouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {

				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

					//Give points
					if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 2;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;
						
					std::cout << "Points: " << this->points << "\n";

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					
				}

			}
		}
		
	}
	else {
		this->isMouseHeld = false;
	}

	
}

void Game::updateText(std::string ss,float x, float y){

	sf::Vector2f position(x, y);
	this->uiText.setPosition(position);
	this->uiText.setString(ss);
}

void Game::renderText(sf::RenderTarget& target){
	
	target.draw(this->uiText);

}

void Game::renderEnemies(sf::RenderTarget& target)
{

	for (auto& e : this->enemies) {

		target.draw(e);

	}

}

void Game::update()
{

	this->pollEvents();
	this->updateMousePositions();

		if (this->endGame == false) {
			std::stringstream ss;

			ss << "Points: " << this->points << "\n"
				<< "Health: " << this->health;
			this->updateText(ss.str(),0.f,0.f);
			this->updateEnemies();

		}
		else {
			this->updateText("Game Over!",350.f,250.f);
		}

	//Endgame condition
	if (this->health <= 0) {

		this->endGame = true;
	}

}

void Game::render()
{

	/*

	- clear old frame
	- render objects
	- display frame in window

	*/


	this->window->clear();
	
	//Draw game objects
	this->renderEnemies(*this->window); 
	this->renderText(*this->window); // the target is a dereferenced window
	this->window->display();
}
