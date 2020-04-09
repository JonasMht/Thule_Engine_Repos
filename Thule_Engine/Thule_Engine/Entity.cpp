#include "Entity.h"


/*Constructor Destructor*/

Entity::Entity()
{
	this->life = true;
}

Entity::~Entity()
{
}

void Entity::putToSleep(sf::Time& runTime)
{
	this->elapsedTime = runTime;
}

void Entity::wake(sf::Time& runTime)
{
	this->elapsedTime = runTime - this->elapsedTime; // get the time difference since it was put to sleep
}

void Entity::update(const float& delta)
{
}

void Entity::render(sf::RenderTarget* target)
{
}
