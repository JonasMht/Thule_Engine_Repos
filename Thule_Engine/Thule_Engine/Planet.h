#ifndef SPACEENTITY_H
#define SPACEENTITY_H


#include "SpaceEntity.h"

class Planet :
	public SpaceEntity
{
private:
	/*Variables*/
	float distance, rad_angle; //angle are in rad;
	SpaceEntity* G;//Object the Planet is attracted to
	sf::CircleShape shape; //placeholder

	sf::Vertex* path = NULL;
	int sections = (int)distance / 7 + 40;

public:

	void initTrajectory();

	/*Constructors Destructors*/
	Planet(SpaceEntity* G, float distance, float rad_angle);
	virtual ~Planet();

	void updateTrajectory();
	void update(const float& delta);
	void render(sf::RenderTarget* target);

};

#endif // !SPACEENTITY_H
