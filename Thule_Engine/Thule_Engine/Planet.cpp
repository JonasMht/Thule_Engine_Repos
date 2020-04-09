#include "Planet.h"

void Planet::initTrajectory()
{
	this->sections = (int)this->distance / 10 + 60;
	path = new sf::Vertex[this->sections];
}

Planet::Planet(Entity* G, float distance, float rad_angle)
{
	this->distance = distance;
	this->rad_angle = rad_angle;
	this->G = G;
	this->shape.setRadius(2.f);
	this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());//trick to get the origin to the center
	
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setPosition(sf::Vector2f(100.f, 100.f));

	this->initTrajectory();
}

Planet::~Planet()
{
	delete[] path;
}
/*Functions*/

void Planet::putToSleep(sf::Time& runTime)
{
}

void Planet::wake(sf::Time& runTime)
{
}

void Planet::updateTrajectory()
{
	for (int q = 0; q < this->sections; q++)
	{
		float angle = -((q) / (float)(this->sections - 1)) * 2 * PI + rad_angle;
		path[q] = sf::Vertex(sf::Vector2f(this->distance * cos(angle) + G->pos.x, this->distance * sin(angle) + G->pos.y));
		path[q].color = sf::Color(255, 255, 255, (int)(255 - 230 * (1 - 1 / (100 * (float)q / (float)sections + 1))));
	}
}

void Planet::update(const float& delta)
{
	this->rad_angle += (1.f/ distance)*delta; // make it gravitate, to be removed
	this->rad_angle = constrainAngle(this->rad_angle);

	this->pos.x = distance * cos(rad_angle) + G->pos.x;
	this->pos.y = distance * sin(rad_angle) + G->pos.y;

	this->updateTrajectory();
}


void Planet::render(sf::RenderTarget* target)
{
	target->draw(this->path, this->sections, sf::LineStrip);
	shape.setPosition(pos);
	target->draw(this->shape);
}
