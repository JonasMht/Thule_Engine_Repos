#ifndef UI_ENTITY_H
#define UI_ENTITY_H

#include "Source.h"

class Entity
{

public:
	/*Variables*/
	sf::Vector2f pos;
	sf::Time elapsedTime;
	bool life;

	/*Constructor Destructor*/
	Entity();
	virtual ~Entity();

	/*Functions*/
	virtual void putToSleep(sf::Time& runTime);
	virtual void wake(sf::Time& runTime);

	/*Update and render*/
	virtual void update(const float& delta) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

#endif // !UI_ENTITY_H