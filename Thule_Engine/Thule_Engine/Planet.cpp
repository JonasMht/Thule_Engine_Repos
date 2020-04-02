#include "Planet.h"

Planet::Planet(SpaceEntity* G, float radius, float rad_angle)
{
	this->radius = radius;
	this->rad_angle = rad_angle;
	this->G = G;
	this->shape.setRadius(2.f);
	this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());//trick to get the origin to the center
	
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setPosition(sf::Vector2f(100.f, 100.f));
}

Planet::~Planet()
{
}

void Planet::update(const float& delta)
{
	this->rad_angle += (1.f/radius)*delta; // make it gravitate, to be removed
	this->rad_angle = constrainAngle(this->rad_angle);

	this->pos.x = radius * cos(rad_angle) + G->pos.x;
	this->pos.y = radius * sin(rad_angle) + G->pos.y;
}

void Planet::render(sf::RenderTarget* target)
{
	shape.setPosition(pos);
	target->draw(this->shape);
}
