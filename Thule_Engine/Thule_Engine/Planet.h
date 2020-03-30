#ifndef SPACEENTITY_H
#define SPACEENTITY_H


#include "SpaceEntity.h"

class Planet :
	public SpaceEntity
{
private:
	/*Variables*/
	float radius, rad_angle; //angle are in rad;
	SpaceEntity* G;//Object the Planet is attracted to
	sf::CircleShape shape; //placeholder
public:
	/*Constructors Destructors*/
	Planet(SpaceEntity* G, float radius, float rad_angle);
	virtual ~Planet();

	void update(const float& delta);
	void render(sf::RenderTarget* target);

};

#endif // !SPACEENTITY_H
