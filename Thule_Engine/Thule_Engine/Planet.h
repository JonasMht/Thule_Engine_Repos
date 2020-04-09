#ifndef SPACEENTITY_H
#define SPACEENTITY_H


#include "GameUI.h"

class Planet :
	public Entity
{
private:
	/*Variables*/
	float distance, rad_angle; //angle are in rad;
	Entity* G;//Object the Planet is attracted to
	sf::CircleShape shape; //placeholder

	sf::Vertex* path = NULL;
	int sections = (int)distance / 7 + 40;

public:

	void initTrajectory();

	/*Constructors Destructors*/
	Planet(Entity* G, float distance, float rad_angle);
	virtual ~Planet();

	/*Functions*/
	void putToSleep(sf::Time& runTime);
	void wake(sf::Time& runTime);


	void updateTrajectory();
	void update(const float& delta);
	void render(sf::RenderTarget* target);

};

#endif // !SPACEENTITY_H
