#ifndef PLANET_H
#define PLAET_H

#include "Planet.h"


class Sun :
	public SpaceEntity //Base class for all objects
{
private:
protected: // variables can be accessed in child class (not like private variable)
	sf::CircleShape shape; //placeholder

public:
	/*Constructors Destructors*/
	Sun(const float posX, const float posY);
	virtual ~Sun();

	/*Functions*/

	void update(const float& delta);
	void render(sf::RenderTarget* target);

};

#endif // !PLANET_H
