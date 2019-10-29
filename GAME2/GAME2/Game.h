#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>


#include "Player.h"
#include "Ball.h"

class Game
{
private:

	Player player;

	sf::VideoMode videoMode;
	sf::RenderWindow* window; // Window that can serve as a target of drawing
	sf::Event sfmlEvent;


	std::vector<Ball> Balls;
	float spawnTimerMax;
	float spawnTimer;
	unsigned int maxBalls;
	int points;
	bool endGame;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	void initVariables();
	void initWindow();
	void initFont();
	void initText();


public:

	//Accessors
	const bool& getEndGame() const;

	//Modifiers


	//Functions
	void spawnBalls();
	void updateCollision();
	const int randomizeType() const;
	const bool running() const;
	void pollEvents();
	void updateGui();
	void updatePlayer();
	void update();
	void render();
	void renderGui(sf::RenderTarget* target);

	//Constructors and destructors
	Game();
	~Game();
};

