#include "Ball.h"

void Ball::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color;
	switch (this->type) {
	case ballTypes::DEFAULT:
		color = sf::Color::Blue;
		break;
	case ballTypes::DAMAGING:
		color = sf::Color::Red;
		break;
	case ballTypes::HEALING:
		color = sf::Color::Green;
		break;
	}
	
	this->shape.setFillColor(color);

	this->shape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand()%window.getSize().x - this->shape.getGlobalBounds().width), 
			static_cast<float>(rand()%window.getSize().y - this->shape.getGlobalBounds().height)
		)
	);
}

Ball::Ball(const sf::RenderWindow& window, int type) 
	: type(type)
{
	this->initShape(window);
}

Ball::~Ball()
{
}

const sf::CircleShape& Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

void Ball::update()
{
}

void Ball::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
