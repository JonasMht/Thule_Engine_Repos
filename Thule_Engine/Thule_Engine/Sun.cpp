#include "Sun.h"

/*Constructors Destructors*/

Sun::Sun(const float posX, const float posY)
{
	this->shape.setRadius(10.f);
	this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());//trick to get the origin to the center
	
	this->pos.x = posX;
	this->pos.y = posY;
	
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setPosition(sf::Vector2f(100.f,100.f));
}

Sun::~Sun()
{
	
}


/*Functions*/



void Sun::update(const float& delta)
{
	
}

void Sun::render(sf::RenderTarget* target)
{
	shape.setPosition(sf::Vector2f(pos.x,pos.y));
	target->draw(this->shape);
}
