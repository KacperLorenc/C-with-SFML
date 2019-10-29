#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Game engine

class Game
{
private:
	
	//Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	
	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources 
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endGame;
	int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;
	bool isMouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:

	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const; // second const means that function doesn't modify the class
	const bool getEndGame() const;

	//Functions
	void spawnEnemies();
	void pollEvents();

	void updateMousePositions();
	void updateEnemies();
	void updateText(std::string ss, float x, float y);
	void update();

	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);	// Good habit ;)
	void render();
};

